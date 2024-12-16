/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:30:28 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/08/01 15:34:18 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	while_export(char *all, int *len, int *a, char *string)
{
	while (string[(*a)] != '\0')
	{
		all[(*len)] = string[(*a)];
		(*len)++;
		(*a)++;
	}
}

void	util_export(char **env, int *a, int *len, char *all)
{
	char	*s;

	s = ft_strchr(*env, '=');
	while ((*env)[(*a)] != '=')
	{
		all[(*len)] = (*env)[(*a)];
		(*len)++;
		(*a)++;
	}
	(*a) = 0;
	all[(*len)++] = s[(*a)++];
	all[(*len)++] = '"';
	while (s[(*a)] != '\0')
	{
		all[(*len)] = s[(*a)];
		(*len)++;
		(*a)++;
	}
	all[(*len)++] = '"';
}

void	sort_indexes(char **order_env)
{
	int		i;
	int		j;
	char	*swap;

	i = 0;
	while (order_env[i] != NULL)
	{
		j = i + 1;
		while (order_env[j] != NULL)
		{
			if (ft_strncmp(order_env[i], order_env[j],
					ft_strlen(order_env[i])) > 0)
			{
				swap = order_env[i];
				order_env[i] = order_env[j];
				order_env[j] = swap;
			}
			j++;
		}
		i++;
	}
}

void	export_only(t_minishell *s_minishell, t_fds fd_redirect)
{
	t_env_list	*temp;
	char		**order_env;
	int			env_len;

	temp = s_minishell->envp;
	env_len = ft_lstsize(temp);
	order_env = ft_calloc(env_len + 1, sizeof(char *));
	if (order_env == NULL)
		return ;
	env_len = 0;
	while (temp != NULL)
	{
		order_env[env_len++] = temp->content;
		temp = temp->next;
	}
	sort_indexes(order_env);
	print_diferent(order_env, fd_redirect.fd_out);
	free(order_env);
}

void	heredoc_update(t_minishell *s_minishell)
{
	if (s_minishell->heredoc_names != NULL)
	{
		s_minishell->current_heredoc = s_minishell->heredoc_names[0];
		move_matrix(s_minishell->heredoc_names, 0);
	}
}
