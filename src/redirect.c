/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:38:22 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/25 16:22:04 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirect(char **splited_prompt)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (splited_prompt[count] != NULL)
	{
		if ((splited_prompt[count][0] == '<' || \
				splited_prompt[count][0] == '>' ) && \
					ft_strlen(splited_prompt[count]) <= 2)
		{
			free(splited_prompt[count]);
			count++;
			free(splited_prompt[count]);
			i = count;
			while (splited_prompt[i] != NULL)
			{
				splited_prompt[i - 1] = splited_prompt[i + 1];
				i++;
			}		
			count = count - 2;
		}
		count++;
	}
}

t_fds	find_redirect(t_minishell *s_minishell)
{
	t_fds	fd_redirect;
	int		count;

	fd_redirect.fd_in = STDIN_FILENO;
	fd_redirect.fd_out = STDOUT_FILENO;
	count = 0;
	while (s_minishell->current_cmd[count] != NULL)
	{
		if (s_minishell->current_cmd[count][0] == '>' && \
			ft_strlen(s_minishell->current_cmd[count]) <= 2)
			right_redirect(s_minishell, &fd_redirect, &count);
		else if (s_minishell->current_cmd[count][0] == '<' &&
			ft_strlen(s_minishell->current_cmd[count]) <= 2)
			left_redirect(s_minishell, &fd_redirect, &count);
		count++;
		if (fd_redirect.fd_in == -1 || fd_redirect.fd_out == -1)
		{
			s_minishell->exit_status = 1;
			break ;
		}
	}
	return (fd_redirect);
}

void	left_redirect(t_minishell *s_minishell,
			t_fds *fd_redirect, int *count)
{
	if (fd_redirect->fd_in != STDIN_FILENO)
		close (fd_redirect->fd_in);
	if (s_minishell->current_cmd[(*count) + 1][0] != '\0')
	{
		if (s_minishell->current_cmd[(*count)][1] == '<')
			fd_redirect->fd_in = open(s_minishell->current_heredoc, O_RDONLY);
		else
			fd_redirect->fd_in = open(s_minishell->current_cmd[(*count) + 1],
					O_RDONLY);
	}
	else
	{
		fd_redirect->fd_out = -2;
		print_error(s_minishell->current_cmd[(*count) + 1],
			": ambiguos redirect");
	}
}

void	right_redirect(t_minishell *s_minishell,
			t_fds	*fd_redirect, int *count)
{
	if (fd_redirect->fd_out != STDOUT_FILENO)
		close (fd_redirect->fd_out);
	if (s_minishell->current_cmd[(*count) + 1][0] != '\0')
	{
		if (s_minishell->current_cmd[(*count)][1] == '>')
			fd_redirect->fd_out = open (s_minishell->current_cmd[(*count) + 1],
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd_redirect->fd_out = open (s_minishell->current_cmd[(*count) + 1],
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else
	{
		fd_redirect->fd_out = -2;
		print_error(s_minishell->current_cmd[(*count) + 1],
			": ambiguos redirect");
	}
}
