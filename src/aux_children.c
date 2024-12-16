/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_children.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:43:35 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/25 14:38:10 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_pipes(t_minishell *s_minishell)
{
	int	i;
	int	count_pipes;

	i = 0;
	count_pipes = 0;
	while (s_minishell->splited_prompt[i] != NULL)
	{
		if (s_minishell->splited_prompt[i][0] == '|')
			count_pipes++;
		i++;
	}
	return (count_pipes);
}

void	cleanup_children(t_minishell *s_minishell)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free_all(s_minishell->current_cmd);
	free_list(s_minishell->envp);
	free_all(s_minishell->heredoc_names);
	free(s_minishell->current_heredoc);
	exit(s_minishell->exit_status);
}

void	wait_children(int *fork_return, t_minishell *s_minishell)
{
	int	i;

	i = 0;
	while (fork_return[i] != -42)
	{
		waitpid(fork_return[i], &s_minishell->exit_status, 0);
		s_minishell->exit_status = WEXITSTATUS(s_minishell->exit_status);
		i++;
	}	
}

void	dup_redirect(t_fds fd_redirect)
{
	if (fd_redirect.fd_in != STDIN_FILENO)
	{
		dup2(fd_redirect.fd_in, STDIN_FILENO);
		close(fd_redirect.fd_in);
	}
	if (fd_redirect.fd_out != STDOUT_FILENO)
	{
		dup2(fd_redirect.fd_out, STDOUT_FILENO);
		close(fd_redirect.fd_out);
	}
}
