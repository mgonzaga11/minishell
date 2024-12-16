/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:15:30 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/08/01 15:29:46 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	util_heredoc(char **limit, t_minishell *s_minishell,
			int *count, int *count_command)
{
	(*count)++;
	(*limit) = s_minishell->splited_prompt[(*count)];
	free(s_minishell->heredoc_names[(*count_command)]);
	s_minishell->heredoc_names[(*count_command)] = get_heredoc_name();
}

int	count_digits(int i)
{
	int	count;

	count = 1;
	while (i >= 10)
	{
		i = i / 10;
		count++;
	}
	return (count);
}

void	walk_index_quotes(char	*input, int *i)
{
	(*i)++;
	while (input[(*i)] != -21 && input[(*i)] != '\0')
		(*i)++;
	(*i)++;
}

void	malloc_var_process(t_minishell *s_minishell,
			char *result, int *len, int *i)
{
	char	*str_exit_status;

	str_exit_status = ft_itoa(s_minishell->exit_status);
	ft_strlcpy(result + (*len), str_exit_status,
		ft_strlen(str_exit_status) + 1);
	(*len) = (*len) + ft_strlen(str_exit_status);
	(*i) = (*i) + 2;
	free(str_exit_status);
}

void	sig_pipe_error(int sig)
{
	(void) sig;
	rl_on_new_line();
	rl_replace_line("", 0);
}
