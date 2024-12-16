/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:07:47 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/25 13:16:59 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	s_minishell;

	(void)argc;
	(void)argv;
	ft_bzero(&s_minishell, sizeof(t_minishell));
	s_minishell.envp = duplic_envp(envp);
	minishell(&s_minishell);
	rl_clear_history();
	close(STDIN_FILENO);
	printf("exit\n");
	return (0);
}
