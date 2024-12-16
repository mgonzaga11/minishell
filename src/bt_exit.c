/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:20:11 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/08/01 15:29:46 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_exit(t_minishell *s_minishell, t_fds fd_redirect)
{
	printf("exit\n");
	handle_exit_arguments(s_minishell);
	cleanup_and_exit(s_minishell, fd_redirect);
}

void	handle_exit_arguments(t_minishell *s_minishell)
{
	if (s_minishell->current_cmd[1] != NULL
		&& s_minishell->current_cmd[2] != NULL)
	{
		if (is_numeric_argument(s_minishell->current_cmd[1]))
		{
			print_error (s_minishell->current_cmd[0], ": too many arguments");
			s_minishell->exit_status = 1;
		}
		else
		{
			s_minishell->exit_status = 2;
			print_error (s_minishell->current_cmd[0], ": too many arguments");
		}
	}
	else if (s_minishell->current_cmd[1] != NULL)
	{
		if (!is_numeric_argument(s_minishell->current_cmd[1]))
		{
			print_error (s_minishell->current_cmd[0], ": non numeric argument");
			s_minishell->exit_status = 2;
		}
		else
			s_minishell->exit_status = ft_atoi(s_minishell->current_cmd[1]);
	}
}

int	is_numeric_argument(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (ft_isdigit(arg[i]) != 0)
		i++;
	return (arg[i] == '\0' && i > 0);
}

void	cleanup_and_exit(t_minishell *s_minishell, t_fds fd_redirect)
{
	free_all (s_minishell->current_cmd);
	free_all (s_minishell->heredoc_names);
	free_all (s_minishell->splited_prompt);
	free (s_minishell->current_heredoc);
	free_list (s_minishell->envp);
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	if (fd_redirect.fd_out != STDOUT_FILENO)
		close (fd_redirect.fd_out);
	if (fd_redirect.fd_in != STDIN_FILENO)
		close (fd_redirect.fd_in);
	printf("exit\n");
	exit (s_minishell->exit_status);
}
