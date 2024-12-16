/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:35:39 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/22 19:18:36 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc(char	**prompt)
{
	int	count;
	int	lines;

	lines = 0;
	count = 0;
	while (prompt[lines] != NULL)
	{
		if (prompt[lines][0] == '<' && (prompt[lines][1] == '<'))
		{
			count++;
			lines++;
		}
		else
			lines++;
	}
	if (count > 0)
		return (1);
	else
		return (0);
}

int	find_pipe(char **splited_prompt)
{
	int	i;

	i = 0;
	while (splited_prompt[i] != NULL)
	{
		if (splited_prompt[i][0] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	check_prompt(char *prompt)
{
	if (check_empty(prompt))
		return (-1);
	add_history(prompt);
	if (only_space(prompt))
		return (-1);
	if (check_quotes(prompt))
	{
		printf("invalid quotes\n");
		return (-1);
	}
	if (check_redirect(prompt))
	{
		printf("error redirect\n");
		return (-1);
	}
	if (check_pipes(prompt))
	{
		printf("syntax error near unexpected token `|'\n");
		return (-1);
	}
	return (0);
}
