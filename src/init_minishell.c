/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:46:48 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/24 20:50:53 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

void	minishell(t_minishell *s_minishell)
{
	int	bkp_fd;

	while (1)
	{
		bkp_fd = dup(STDIN_FILENO);
		handle_signals();
		s_minishell->input = readline("shellzinho: ");
		if (!s_minishell->input)
		{
			if (g_signal == SIGINT)
			{
				s_minishell->exit_status = 130;
				g_signal = 0;
				dup2(bkp_fd, STDIN_FILENO);
				close(bkp_fd);
				continue ;
			}
			close(bkp_fd);
			free_list(s_minishell->envp);
			break ;
		}
		process_input(s_minishell, bkp_fd);
	}
}

void	process_input(t_minishell *s_minishell, int bkp_fd)
{
	if (check_prompt(s_minishell->input) < 0)
	{
		free(s_minishell->input);
		close(bkp_fd);
		return ;
	}
	s_minishell->norm_prompt = norme_string(s_minishell->input);
	free(s_minishell->input);
	if (!s_minishell->norm_prompt)
	{
		printf("error\n");
		close(bkp_fd);
		return ;
	}
	new_prompt(s_minishell->norm_prompt);
	s_minishell->splited_prompt = ft_split(s_minishell->norm_prompt, -42);
	free(s_minishell->norm_prompt);
	if (!s_minishell->splited_prompt)
	{
		printf("error\n");
		close(bkp_fd);
		return ;
	}
	handle_commands(s_minishell, bkp_fd);
	free_all(s_minishell->splited_prompt);
}

void	handle_commands(t_minishell *s_minishell, int bkp_fd)
{
	if (check_heredoc(s_minishell->splited_prompt) == 1)
	{
		if (heredoc(s_minishell) == 1)
		{
			dup2(bkp_fd, STDIN_FILENO);
			close(bkp_fd);
			return ;
		}
		dup2(bkp_fd, STDIN_FILENO);
	}
	close(bkp_fd);
	if (find_pipe(s_minishell->splited_prompt) == 1)
	{
		more_command(s_minishell);
	}
	else
	{
		single_cmd(s_minishell);
	}
	if (s_minishell->heredoc_names != NULL)
		free_all(s_minishell->heredoc_names);
	s_minishell->heredoc_names = NULL;
	if (s_minishell->current_cmd != NULL)
		free_all(s_minishell->current_cmd);
	s_minishell->current_cmd = NULL;
}

void	single_cmd(t_minishell *s_minishell)
{
	s_minishell->current_cmd = s_minishell->splited_prompt;
	s_minishell->splited_prompt = NULL;
	if (s_minishell->heredoc_names != NULL)
	{
		s_minishell->current_heredoc = s_minishell->heredoc_names[0];
		free(s_minishell->heredoc_names);
		s_minishell->heredoc_names = NULL;
	}
	bt_or_exec(s_minishell);
	free (s_minishell->current_heredoc);
	s_minishell->current_heredoc = NULL;
}

t_env_list	*duplic_envp(char	**envp)
{
	int			count_lines;
	t_env_list	*new_envp;

	new_envp = NULL;
	count_lines = 0;
	while (envp[count_lines] != NULL)
	{
		if (new_envp == NULL)
			new_envp = ft_lstnew(ft_strdup(envp[count_lines]));
		else
			ft_lstadd_back(&new_envp, ft_lstnew(ft_strdup(envp[count_lines])));
		count_lines++;
	}
	return (new_envp);
}
