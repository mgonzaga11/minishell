/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:03:09 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/25 16:23:10 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*norme_string(char *prompt)
{
	int		count;
	char	*result;
	int		count_result;

	count_result = 0;
	count = 0;
	result = malloc_prompt(prompt);
	if (result == NULL)
		return (NULL);
	while (prompt[count] != '\0')
	{
		if (prompt[count] == '\'' || prompt[count] == '"')
			copy_quotes(&count, prompt, &count_result, result);
		else if (prompt[count] == '>' || prompt[count] == '<'
			|| prompt[count] == '|')
		{
			norme_char(&count, &count_result, result, prompt);
		}
		else
			result[count_result++] = prompt[count++];
	}
	result[count_result] = '\0';
	return (result);
}

char	*malloc_prompt(char *prompt)
{
	int		size_prompt;
	int		count;
	char	*result;

	count = 0;
	size_prompt = ft_strlen(prompt);
	while (prompt[count] != '\0')
	{
		if (prompt[count] == '>' || prompt[count] == '<'
			|| prompt[count] == '|')
			size_prompt = size_prompt + 2;
		count++;
	}
	result = malloc((size_prompt + 1) * sizeof(char));
	return (result);
}

void	norme_char(int *count, int *count_result, char	*result, char	*prompt)
{
	result[(*count_result)] = ' ';
	(*count_result)++;
	result[(*count_result)] = prompt[(*count)];
	if (prompt[(*count) + 1] == '>' || prompt[(*count) + 1] == '<')
	{
		(*count)++;
		(*count_result)++;
		result[(*count_result)] = prompt[(*count)];
		(*count_result)++;
		result[(*count_result)] = ' ';
		(*count)++;
		(*count_result)++;
	}
	else
	{
		(*count_result)++;
		result[(*count_result)] = ' ';
		(*count_result)++;
		(*count)++;
	}
}

int	count_matrix_len(char **matrix)
{
	int	len;

	len = 0;
	if (matrix == NULL || matrix[0] == NULL)
		return (0);
	while (matrix[len] != NULL)
	{
		len++;
	}
	return (len);
}
