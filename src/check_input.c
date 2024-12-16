/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:12:45 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/25 16:23:40 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipes(char *prompt)
{
	int	count;

	count = 0;
	while (prompt[count] == ' ' || prompt[count] == '	')
		count++;
	if (prompt[count] == '|')
		return (-1);
	while (prompt[count] != '\0')
	{
		if (prompt[count] == 34 || prompt[count] == 39)
			ignore_quotes(&count, prompt);
		else if (prompt[count] == '|')
		{
			count++;
			while (prompt[count] == ' ' || prompt[count] == '	')
				count++;
			if (prompt[count] == '\0' || prompt[count] == '|')
				return (-1);
		}
		else
			count++;
	}
	return (0);
}

int	check_quotes(char *prompt)
{
	int	i;
	int	quotes;
	int	checker;

	checker = 0;
	i = -1;
	while (prompt[++i] != '\0')
	{
		if (prompt[i] == 34 || prompt[i] == 39)
		{
			quotes = prompt[i];
			if (prompt[i] == 34)
				while (prompt[++i] != 34 && prompt[i] != '\0')
					;
			else if (prompt[i] == 39)
				while (prompt[++i] != 39 && prompt[i] != '\0')
					;
			if (prompt[i] != quotes)
				checker = -1;
		}
		if (prompt[i] == '\0')
			break ;
	}
	return (checker);
}

int	check_redirect(char *prompt)
{
	int	count;

	count = 0;
	while (prompt[count] != '\0')
	{
		if (prompt[count] == 34 || prompt[count] == 39)
			ignore_quotes(&count, prompt);
		else if (prompt[count] == '>' || prompt[count] == '<')
		{
			count++;
			if ((prompt[count] != prompt[count - 1]) && (prompt[count] == '>'
					|| prompt[count] == '<'))
				return (-1);
			else if (prompt[count] == '>' || prompt[count] == '<')
				count++;
			while (prompt[count] == ' ' || prompt[count] == '\t')
				count++;
			if (prompt[count] == '\0' || prompt[count] == '|'
				|| prompt[count] == '>' || prompt[count] == '<')
				return (-1);
		}
		else
			count++;
	}
	return (0);
}

int	only_space(char *prompt)
{
	int	count;

	count = 0;
	while (prompt[count] != '\0')
	{
		if (prompt[count] != ' ' && prompt[count] != '\t')
			return (0);
		count++;
	}
	return (-1);
}

int	check_empty(char *prompt)
{
	if (prompt[0] == '\0')
		return (-1);
	else
		return (0);
}
