/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:16:05 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/24 20:47:49 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bt_env(t_minishell *s_minishell, t_fds fd_redirect)
{
	int			i;
	t_env_list	*envp;

	envp = s_minishell->envp;
	s_minishell->exit_status = 0;
	while (envp != NULL)
	{
		i = 0;
		while (((char *)(envp->content))[i] != '\0')
		{
			if (((char *)envp->content)[i] == '=')
			{
				ft_putendl_fd (((char *)envp->content), fd_redirect.fd_out);
				break ;
			}
			i++;
		}		
		envp = envp->next;
	}
	return (0);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	i = ft_strlen(s);
	s[i] = '\n';
	write(fd, s, i + 1);
	s[i] = '\0';
}
