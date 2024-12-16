/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:36:25 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/24 16:37:08 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_path(char *path)
{
	struct stat	path_status;

	if (path == NULL)
	{
		write(2, "Command not found\n", 19);
		return (127);
	}
	if (access(path, F_OK) != 0)
	{
		write(2, "No such file or directory\n", 27);
		return (127);
	}
	stat(path, &path_status);
	if (S_ISDIR(path_status.st_mode) != 0)
	{
		write(2, "Is a directory\n", 16);
		return (126);
	}
	if (access(path, X_OK) != 0)
	{
		write(2, "Permission denied\n", 19);
		return (126);
	}
	else
		return (42);
}

char	*search_path(char *splited_prompt, t_env_list *envp)
{
	char	*path;
	char	*path_env;
	char	**splited_path;
	int		i;

	i = 0;
	if (splited_prompt[i] == '\0')
		return (NULL);
	if (ft_strchr(splited_prompt, '/') != NULL)
		return (splited_prompt);
	path_env = return_value(envp, "PATH");
	splited_path = ft_split(path_env, ':');
	if (!splited_path)
		return (NULL);
	path = find_path(splited_path, splited_prompt);
	free_all(splited_path);
	return (path);
}

char	*find_path(char **splited_path, char *splited_prompt)
{
	int		i;
	char	*temp;
	char	*path;

	i = 0;
	while (splited_path[i] != NULL)
	{
		temp = ft_strjoin(splited_path[i], "/");
		if (!temp)
			break ;
		path = ft_strjoin(temp, splited_prompt);
		free(temp);
		if (!path)
			break ;
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*return_value(t_env_list *envp, char *var)
{
	char		*value;
	int			len_var;
	t_env_list	*tmp;

	len_var = ft_strlen_2(var);
	tmp = envp;
	while (tmp != NULL)
	{
		value = ft_strnstr(tmp->content, var, len_var);
		if (value != NULL)
		{
			if (tmp->content[len_var] == '=')
				return (&tmp->content[len_var + 1]);
			if (tmp->content[len_var] == '\0')
				return (&tmp->content[len_var]);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
