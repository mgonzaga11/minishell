/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:33:42 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/08/01 17:20:33 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_or_exec(t_minishell *s_minishell)
{
	t_fds	fd_redirect;
	int		need_to_expand;

	need_to_expand = 0;
	if (s_minishell->current_cmd != NULL
		&& s_minishell->current_cmd[0] != NULL)
		need_to_expand = expand_var(s_minishell->current_cmd,
				s_minishell->envp, s_minishell);
	fd_redirect = find_redirect (s_minishell);
	if (fd_redirect.fd_in <= -1 || fd_redirect.fd_out <= -1)
	{
		close_fds(fd_redirect);
		return ;
	}
	free_redirect(s_minishell->current_cmd);
	if (ft_strchr(s_minishell->current_cmd[0], ' ') != NULL && need_to_expand)
		expand_with_command(s_minishell);
	if (s_minishell->current_cmd != NULL
		&& s_minishell->current_cmd[0] != NULL)
		exec_commands (s_minishell, fd_redirect);
	if (fd_redirect.fd_out != STDOUT_FILENO)
		close (fd_redirect.fd_out);
	if (fd_redirect.fd_in != STDIN_FILENO)
		close (fd_redirect.fd_in);
}

void	exec_commands(t_minishell *s_minishell, t_fds	fd_redirect)
{
	int		bt_check;

	bt_check = check_builtin(s_minishell->current_cmd[0]);
	if (bt_check > 0)
		exec_bt(bt_check, s_minishell, (fd_redirect));
	else
		command_exec(s_minishell, (fd_redirect));
}

void	exec_bt(int bt_check, t_minishell *s_minishell, t_fds fd_redirect)
{
	if (bt_check == 1)
		bt_exit(s_minishell, fd_redirect);
	if (bt_check == 2)
		bt_env(s_minishell, fd_redirect);
	if (bt_check == 3)
		bt_echo(s_minishell, fd_redirect);
	if (bt_check == 4)
		bt_pwd(s_minishell, fd_redirect);
	if (bt_check == 5)
		bt_cd(s_minishell);
	if (bt_check == 6)
		bt_export(s_minishell, fd_redirect);
	if (bt_check == 7)
		bt_unset(s_minishell);
}
