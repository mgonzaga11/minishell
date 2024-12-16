/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:06:53 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/23 13:51:14 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ignore_quotes(int *count, char *prompt)
{
	char	quote;

	quote = prompt[(*count)];
	(*count)++;
	while (prompt[(*count)] != quote)
		(*count)++;
	(*count)++;
}

int	pipes_count(char **prompt)
{
	int	count;
	int	count_pipes;

	count = 0;
	count_pipes = 0;
	while (prompt[count] != NULL)
	{
		if (prompt[count][0] == '|')
			count_pipes++;
		count++;
	}
	return (count_pipes);
}

void	new_prompt(char *prompt)
{
	int		count;
	char	quote;

	count = 0;
	while (prompt[count] != '\0')
	{
		if (prompt[count] == '"' || prompt[count] == '\'')
		{
			quote = prompt[count++];
			while (prompt[count] != quote)
				count++;
			count++;
		}
		else
		{
			if (prompt[count] == ' ' || prompt[count] == '	')
				prompt[count] = -42;
			count++;
		}
	}
}

int	check_builtin(char *splited_prompt)
{
	if (!ft_memcmp(splited_prompt, EXIT, ft_strlen(EXIT))
		&& !ft_memcmp(splited_prompt, EXIT, ft_strlen(splited_prompt)))
		return (1);
	if (!ft_memcmp(splited_prompt, ENV, ft_strlen(ENV))
		&& !ft_memcmp(splited_prompt, ENV, ft_strlen(splited_prompt)))
		return (2);
	if (!ft_memcmp(splited_prompt, ECHO_CMD, ft_strlen(ECHO_CMD))
		&& !ft_memcmp(splited_prompt, ECHO_CMD, ft_strlen(splited_prompt)))
		return (3);
	if (!ft_memcmp(splited_prompt, PWD, ft_strlen(PWD))
		&& !ft_memcmp(splited_prompt, PWD, ft_strlen(splited_prompt)))
		return (4);
	if (!ft_memcmp(splited_prompt, CD, ft_strlen(CD))
		&& !ft_memcmp(splited_prompt, CD, ft_strlen(splited_prompt)))
		return (5);
	if (!ft_memcmp(splited_prompt, EXPORT, ft_strlen(EXPORT))
		&& !ft_memcmp(splited_prompt, EXPORT, ft_strlen(splited_prompt)))
		return (6);
	if (!ft_memcmp(splited_prompt, UNSET, ft_strlen(UNSET))
		&& !ft_memcmp(splited_prompt, UNSET, ft_strlen(splited_prompt)))
		return (7);
	else
		return (0);
}

void	copy_quotes(int *count, char *prompt, int *len, char *result)
{
	char	quote;

	quote = prompt[(*count)];
	result[(*len)] = prompt[(*count)];
	(*count)++;
	(*len)++;
	while (prompt[(*count)] != quote)
	{
		result[(*len)] = prompt[(*count)];
		(*count)++;
		(*len)++;
	}
	result[(*len)] = prompt[(*count)];
	(*count)++;
	(*len)++;
}
