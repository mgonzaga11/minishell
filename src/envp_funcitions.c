/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_funcitions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:52:36 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/22 19:46:08 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*localize_envp(t_env_list *envp, char *var)
{
	int			value;
	int			len_var;
	t_env_list	*tmp;

	len_var = ft_strlen_2(var);
	tmp = envp;
	while (tmp != NULL)
	{
		value = ft_memcmp (tmp->content, var, len_var);
		if (value == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	valid_var(t_env_list *envp, char *var)
{
	int			value;
	t_env_list	*tmp;

	tmp = envp;
	while (tmp != NULL)
	{
		value = ft_strncmp (tmp->content, var, ft_strlen(tmp->content));
		if (value == 0 || value == '=')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	localize_envp2(t_env_list *envp, char *var)
{
	int			value;
	int			len_var;
	t_env_list	*tmp;

	len_var = ft_strlen_2(var);
	tmp = envp;
	while (tmp != NULL)
	{
		value = ft_memcmp (tmp->content, var, len_var);
		if (value == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
