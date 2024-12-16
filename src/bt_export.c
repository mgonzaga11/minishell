/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:37:07 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/08/01 15:29:13 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_export(t_minishell *s_minishell, t_fds fd_redirect)
{
	int			count;
	int			i;

	count = 1;
	s_minishell->exit_status = 0;
	if (s_minishell->current_cmd[1] == NULL)
		export_only(s_minishell, fd_redirect);
	else
	{
		while (s_minishell->current_cmd[count] != NULL)
		{
			i = 1;
			if (ft_isalpha(s_minishell->current_cmd[count][0]) == 1
			|| s_minishell->current_cmd[count][0] == '_')
			{
				if (valid_export_var_name (&count, &i, s_minishell) == 1)
					find_inenvp_export(s_minishell, &count, &i);
			}
			else
				s_minishell->exit_status = print_error(\
					s_minishell->current_cmd[count], \
						": not a valid identifier");
			count++;
		}
	}
}

void	print_diferent(char **env, int fd)
{
	int		len;
	char	*all;
	char	*s;
	int		a;

	while (*env != NULL)
	{
		len = 0;
		a = ft_strlen(*env);
		all = calloc((a + 17), sizeof(char));
		s = "declare -x ";
		a = 0;
		while_export(all, &len, &a, s);
		len = 12;
		a = 0;
		if (ft_strchr(*env, '=') != NULL)
			util_export(env, &a, &len, all);
		else
			while_export(all, &len, &a, *env);
		all[len++] = '\n';
		all[len] = '\0';
		write(fd, all, len);
		free(all);
		env++;
	}
}

void	find_inenvp_export(t_minishell *s_minishell, int *count, int *i)
{
	t_env_list	*local;

	if (localize_envp2(s_minishell->envp,
			s_minishell->current_cmd[(*count)]) == 1)
	{
		if (s_minishell->current_cmd[(*count)][(*i)] == '=')
		{
			local = localize_envp(s_minishell->envp,
					s_minishell->current_cmd[(*count)]);
			free(local->content);
			local->content = ft_strdup(s_minishell->current_cmd[(*count)]);
		}
	}
	else
		ft_lstadd_back (&s_minishell->envp,
			ft_lstnew(ft_strdup(s_minishell->current_cmd[(*count)])));
}

int	valid_export_var_name(int *count, int *i, t_minishell *s_minishell)
{
	while (s_minishell->current_cmd[(*count)][(*i)] != '\0'
		&& s_minishell->current_cmd[(*count)][(*i)] != '=')
	{
		if (ft_isalnum((s_minishell->current_cmd)[*count][*i]) == 1
		|| ((s_minishell->current_cmd))[(*count)][(*i)] == '_')
			(*i)++;
		else
		{
			print_error(s_minishell->current_cmd[(*count)],
				": not a valid identifier");
			s_minishell->exit_status = 1;
			return (0);
		}
	}
	return (1);
}
