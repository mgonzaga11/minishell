/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:33:57 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/25 15:32:38 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	more_command(t_minishell *s_minishell)
{
	int	*fork_return;
	int	count_pipes;

	count_pipes = ft_count_pipes(s_minishell);
	fork_return = malloc((count_pipes + 2) * sizeof(int));
	if (!fork_return)
		return ;
	handle_pipes(s_minishell, fork_return, count_pipes);
	fork_return[count_pipes + 1] = -42;
	wait_children(fork_return, s_minishell);
	free(fork_return);
}

void	handle_pipes(t_minishell *s_minishell, int *fork_return,
		int count_pipes)
{
	int	j;
	int	fds[2];
	int	fd_bkp;

	j = -1;
	fd_bkp = STDIN_FILENO;
	while (count_pipes >= 0)
	{
		heredoc_update(s_minishell);
		if (count_pipes > 0)
			pipe(fds);
		fork_return[++j] = fork();
		sig_execute(fork_return[j]);
		if (fork_return[j] == 0)
		{
			free(fork_return);
			prep_and_execute(s_minishell, fds, &fd_bkp, count_pipes);
		}
		else
		{
			free(s_minishell->current_heredoc);
			ready_for_next (s_minishell, fds, &fd_bkp, count_pipes);
			count_pipes--;
		}
	}
}

void	prep_and_execute(t_minishell *s_minishell, int fds[2],
			int *fd_bkp, int count_pipes)
{
	rl_clear_history();
	get_command_and_cleanup(s_minishell);
	if (count_pipes > 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		close(fds[0]);
	}
	dup2(*fd_bkp, STDIN_FILENO);
	if (*fd_bkp != 0)
		close(*fd_bkp);
	bt_or_exec(s_minishell);
	cleanup_children(s_minishell);
}

void	ready_for_next(t_minishell *s_minishell, int fds[2],
		int *fd_bkp, int count_pipes)
{
	free_all(get_command(s_minishell->splited_prompt));
	if (*fd_bkp != STDIN_FILENO)
		close(*fd_bkp);
	*fd_bkp = fds[0];
	if (count_pipes > 0)
		close(fds[1]);
}

void	get_command_and_cleanup(t_minishell *s_minishell)
{
	s_minishell->current_cmd = get_command(s_minishell->splited_prompt);
	free_all(s_minishell->splited_prompt);
	free_all(s_minishell->heredoc_names);
	s_minishell->splited_prompt = NULL;
	s_minishell->heredoc_names = NULL;
}
