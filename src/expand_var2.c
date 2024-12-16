/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:13:15 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/24 13:13:30 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_len_process(char *input, int *len, int *i, t_env_list *envp)
{
	char	*substr;
	int		var_len;

	var_len = (*i);
	while ((ft_isalnum(input[var_len]) == 1 || input[var_len] == '_')
		&& input[var_len] != '\0')
		var_len++;
	substr = ft_substr(input, (*i), var_len - (*i));
	if (substr == NULL)
		(*len) = 0;
	else
	{
		i = &var_len;
		(*len) = (*len) - ft_strlen(substr);
		(*len) = (*len) + ft_strlen(return_value(envp, substr));
	}
	free(substr);
}

char	*malloc_var(char *input, t_env_list *envp, t_minishell *s_minishell)
{
	int		len;
	char	*result;

	len = malloc_len(input, envp, s_minishell);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	process_malloc(input, envp, s_minishell, result);
	free(input);
	return (result);
}

void	process_malloc(char *input, t_env_list *envp, t_minishell *s_minishell,
		char *result)
{
	int		i;
	int		len;
	char	*substr;

	i = 0;
	len = 0;
	while (input[i] != '\0')
	{
		if (input[i] == -21)
			walk_simple_quote(&i, input, result, &len);
		else if (input[i] == '$' && input[i + 1] == '?')
			malloc_var_process(s_minishell, result, &len, &i);
		else if (input[i] == '$' && (ft_isalpha(input[i + 1]) == 1
				|| input[i + 1] == '_'))
		{
			substr = put_substr(&i, input);
			put_result(substr, &len, envp, result);
			free(substr);
		}
		else
			result[len++] = input[i++];
	}
}

void	walk_simple_quote(int *i, char *input, char *result, int *len)
{
	result[(*len)] = input[(*i)];
	(*i)++;
	(*len)++;
	while (input[(*i)] != -21 && input[(*i)] != '\0')
	{
		result[(*len)] = input[(*i)];
		(*len)++;
		(*i)++;
	}
	result[(*len)] = input[(*i)];
	(*len)++;
	(*i)++;
}

void	put_result(char *substr, int *len, t_env_list *envp, char *result)
{
	int	var_len;

	if (valid_var(envp, substr) == 1)
	{
		substr = return_value(envp, substr);
		var_len = 0;
		while (substr[var_len] != '\0')
		{
			result[(*len)] = substr[var_len];
			(*len)++;
			var_len++;
		}
	}
}
