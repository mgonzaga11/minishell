/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:17:20 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/25 13:16:09 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_pwd(t_minishell *s_minishell, t_fds fd_redirect)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ft_putstr_fd("I can't show you the path!!\n", 2);
		return ;
	}
	ft_putstr_fd(path, fd_redirect.fd_out);
	ft_putstr_fd("\n", fd_redirect.fd_out);
	s_minishell->exit_status = 0;
	free(path);
}
