/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commnad.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:13:41 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/24 18:46:43 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**execve_envp(t_env_list *envp)
{
	char		**other_envp;
	t_env_list	*tmp;
	int			i;

	tmp = envp;
	i = ft_lstsize(tmp);
	other_envp = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (tmp != NULL)
	{
		other_envp[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	other_envp[i] = NULL;
	return (other_envp);
}

void	command_exec(t_minishell *s_minishell, t_fds fd_redirect)
{
	char	*path;
	int		exit_status;
	int		fork_return;

	fork_return = (fork());
	sig_execute(fork_return);
	if (fork_return == -1)
		return ;
	if (fork_return == 0)
	{
		rl_clear_history();
		path = search_path(s_minishell->current_cmd[0], s_minishell->envp);
		dup_redirect(fd_redirect);
		exit_status = valid_path(path);
		if (exit_status == 42)
			finally_exec(s_minishell, path);
		if (path != s_minishell->current_cmd[0])
			free(path);
		free_close_exec(s_minishell, exit_status);
	}
	else
		wait(&s_minishell->exit_status);
	s_minishell->exit_status = WEXITSTATUS(s_minishell->exit_status);
}

void	finally_exec(t_minishell *s_minishell, char *path)
{
	char	**temp_envp;

	temp_envp = execve_envp(s_minishell->envp);
	execve(path, s_minishell->current_cmd, temp_envp);
	free_all(temp_envp);
}

char	**get_command(char **splited_prompt)
{
	int		i;
	int		count_lines;
	char	**command;

	i = 0;
	count_lines = 0;
	while (splited_prompt[i] != NULL)
	{
		if (splited_prompt[i][0] == '|')
			break ;
		count_lines++;
		i++;
	}
	command = malloc((count_lines + 1) * sizeof(char *));
	if (!command)
		return (NULL);
	free(splited_prompt[i]);
	i = 0;
	while_get_command(command, splited_prompt, &i, &count_lines);
	i = 0;
	while (splited_prompt[count_lines] != NULL)
		splited_prompt[i++] = splited_prompt[++count_lines];
	splited_prompt[i] = NULL;
	return (command);
}

void	while_get_command(char **command, char **splited_prompt, int *i,
		int *count_lines)
{
	while ((*i) < (*count_lines))
	{
		command[(*i)] = splited_prompt[(*i)];
		(*i)++;
	}
	command[(*i)] = NULL;
}
