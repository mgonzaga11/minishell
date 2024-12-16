/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:39:06 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/24 16:48:37 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(char **malloc_string)
{
	int	count;

	count = 0;
	if (malloc_string == NULL)
		return ;
	while (malloc_string[count] != NULL)
	{
		free(malloc_string[count]);
		count++;
	}
	free(malloc_string);
}

void	free_list(t_env_list *envp)
{
	t_env_list	*current_node;
	t_env_list	*next_node;

	current_node = envp;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node->content);
		free(current_node);
		current_node = next_node;
	}
}

void	free_close_exec(t_minishell *s_minishell, int exit_status)
{
	free_all(s_minishell->current_cmd);
	free_all(s_minishell->splited_prompt);
	free_list(s_minishell->envp);
	free_all(s_minishell->heredoc_names);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(exit_status);
}

void	free_heredocs_but_not_index(char **heredocs, int index)
{
	int	i;

	if (heredocs == NULL || heredocs[0] == NULL)
		return ;
	i = 0;
	while (heredocs[i] != NULL)
	{
		if (i != index)
			free(heredocs[i]);
		i++;
	}
	free(heredocs);
}
