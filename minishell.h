/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:13:50 by izanoni           #+#    #+#             */
/*   Updated: 2024/08/01 15:38:06 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>	
# include <signal.h>

# include "./libft/libft.h"

# define EXIT "exit"
# define ECHO_CMD "echo"
# define PWD "pwd"
# define ENV "env"
# define CD "cd"
# define EXPORT "export"
# define UNSET "unset"
# define DOUBLE_QUOTES '"'
# define SINGLE_QUOTES '\''

extern int	g_signal;

typedef struct s_fd_in_out
{
	int	fd_in;
	int	fd_out;
}	t_fds;

typedef struct s_env_list
{
	char				*content;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_minishell
{
	char		*input;
	char		*norm_prompt;
	char		**splited_prompt;
	char		**current_cmd;
	t_env_list	*envp;
	char		**heredoc_names;
	char		*current_heredoc;
	int			exit_status;
}	t_minishell;

//aux_children
int			ft_count_pipes(t_minishell *s_minishell);
void		cleanup_children(t_minishell *s_minishell);
void		wait_children(int *fork_return, t_minishell *s_minishell);
void		dup_redirect(t_fds fd_redirect);

//bt_cd
void		bt_cd(t_minishell *s_minishell);
int			change_to_home_directory(t_minishell *s_minishell, char *old_path);
int			change_directory(char *dir, t_env_list *envp, char *old_path);
void		update_wd(char *new_path, t_env_list *envp, char *old_path);

//bt_echo
void		bt_echo(t_minishell *s_minishell, t_fds fd_redirect);
int			echo_n(int *n, int *count, int *val, char **splited_prompt);
void		util_echo_n(t_fds fd_redirect, int *count,
				t_minishell	*s_minishel, int *val);
void		util_echo(t_fds fd_redirect, int *count,
				t_minishell *s_minishell, int *val);

//bt_env
int			bt_env(t_minishell	*s_minishell, t_fds	fd_redirect);
void		ft_putendl_fd(char *s, int fd);

//bt_exit
void		bt_exit(t_minishell *s_minishell, t_fds	fd_redirect);
void		handle_exit_arguments(t_minishell *s_minishell);
void		cleanup_and_exit(t_minishell *s_minishell, t_fds fd_redirect);
int			is_numeric_argument(char *arg);

//bt_export
void		bt_export(t_minishell	*s_minishell, t_fds	fd_redirect);
void		print_diferent(char **env, int fd);
void		find_inenvp_export(t_minishell *s_minishell, int *count, int	*i);
int			valid_export_var_name(int *count, int *i, t_minishell *s_minishell);

//bt_pwd
void		bt_pwd(t_minishell	*s_minishell, t_fds fd_redirect);

//bt_unset
char		*bt_unset(t_minishell *s_minishell);
void		process_prompt(char *prompt, t_env_list **envp);
int			should_remove_node(t_env_list *node, char *prompt, int len_var);
void		delnode(t_env_list	**envp, t_env_list	*node);
int			check_name(char *splited_prompt);

//check_command
int			check_heredoc(char	**prompt);
int			find_pipe(char **splited_prompt);
int			check_prompt(char *prompt);

//check_input
int			check_pipes(char *prompt);
int			check_quotes(char *prompt);
int			check_redirect(char *prompt);
int			only_space(char *prompt);
int			check_empty(char *prompt);

//envp_funcitions
t_env_list	*localize_envp(t_env_list *envp, char *var);
int			valid_var(t_env_list *envp, char *var);
int			localize_envp2(t_env_list *envp, char *var);

//error
int			print_error(char *var, char *message);
char		*create_error_message(char *var, char *message);

//exec_command
char		**execve_envp(t_env_list *envp);
void		command_exec(t_minishell *s_minishell, t_fds fd_redirect);
void		finally_exec(t_minishell *s_minishell, char *path);
char		**get_command(char **splited_prompt);
void		while_get_command(char **command, char **splited_prompt, int *i,
				int *count_lines);

//exec_command2
void		bt_or_exec(t_minishell *s_minishell);
void		exec_bt(int bt_check, t_minishell *s_minishell, t_fds fd_redirect);
void		exec_commands(t_minishell *s_minishell, t_fds	fd_redirect);

//expand_var
void		move_matrix(char **splited_prompt, int start);
int			expand_var(char **splited_prompt, t_env_list *envp,
				t_minishell *s_minishell);
void		mod_quots(char *input);
void		remov_quots(char *input);
int			malloc_len(char	*input, t_env_list	*envp,
				t_minishell *s_minishell);

//expand_var2
void		malloc_len_process(char	*input, int *len,
				int *i, t_env_list *envp);
char		*malloc_var(char *input, t_env_list	*envp,
				t_minishell *s_minishell);
void		process_malloc(char *input, t_env_list *envp,
				t_minishell *s_minishell, char *result);
void		walk_simple_quote(int *i, char *input, char *result, int *len);
void		put_result(char *substr, int *len, t_env_list *envp, char *result);

//free_all
void		free_all(char **malloc_string);
void		free_list(t_env_list *envp);
void		free_close_exec(t_minishell *s_minishell, int exit_status);
void		free_heredocs_but_not_index(char **heredocs, int index);

//handle_path
int			valid_path(char *path);
char		*search_path(char *splited_prompt, t_env_list *envp);
char		*find_path(char **splited_path, char *splited_prompt);
char		*return_value(t_env_list	*envp, char *var);

//heredoc
void		initialize_with_empty_strings(char **heredoc_name, int size);
char		*get_heredoc_name(void);
int			heredoc(t_minishell *s_minishell);
int			free_heredoc_names(t_minishell *s_minishell,
				int *count_command, int *fd);
int			heredoc_process(int	*count, t_minishell *s_minishell,
				int *count_command, int *fd);

//init_minishell
void		minishell(t_minishell *s_minishell);
void		process_input(t_minishell *s_minishell, int bkp_fd);
void		handle_commands(t_minishell *s_minishell, int bkp_fd);
void		single_cmd(t_minishell *s_minishell);
t_env_list	*duplic_envp(char	**envp);

//main
int			main(int argc, char **argv, char **envp);

//more_command
void		more_command(t_minishell *s_minishell);
void		handle_pipes(t_minishell *s_minishell, int *fork_return,
				int count_pipes);
void		prep_and_execute(t_minishell *s_minishell, int fds[2],
				int *fd_bkp, int count_pipes);
void		ready_for_next(t_minishell *s_minishell, int fds[2],
				int *fd_bkp, int count_pipes);
void		get_command_and_cleanup(t_minishell *s_minishell);

//norme_prompt
char		*norme_string(char *prompt);
char		*malloc_prompt(char *prompt);
void		norme_char(int *count, int *count_result,
				char *result, char *prompt);
int			count_matrix_len(char **matrix);

//redirect
void		free_redirect(char **splited_prompt);
t_fds		find_redirect(t_minishell *s_minishell);
void		left_redirect(t_minishell *s_minishell,
				t_fds	*fd_redirect, int *count);
void		right_redirect(t_minishell *s_minishell,
				t_fds	*fd_redirect, int *count);

//signals
void		handle_signals(void);
void		sig_ctrl_c(int sig);
void		end_heredoc(int sig);
void		sig_heredoc(void);
void		sig_execute(int child_pid);

//t_list_funcitions
void		ft_lstadd_back(t_env_list **lst, t_env_list *new);
t_env_list	*ft_lstlast(t_env_list *lst);
t_env_list	*ft_lstnew(void *content);
int			ft_lstsize(t_env_list *lst);

//utils_bt_or_exec
void		close_fds(t_fds fd_redirect);
void		expand_with_command(t_minishell *s_minishell);
char		*put_substr(int *i, char *input);
size_t		ft_strlen_2(const char *s);

//utils_export
void		while_export(char	*all, int *len, int *a, char *string);
void		util_export(char **env, int *a, int *len, char *all);
void		export_only(t_minishell *s_minishell, t_fds fd_redirect);
void		heredoc_update(t_minishell *s_minishell);
void		sort_indexes(char **order_env);

//utils_fincitions
void		ignore_quotes(int *count, char *prompt);
int			pipes_count(char **prompt);
void		new_prompt(char *prompt);
int			check_builtin(char *splited_prompt);
void		copy_quotes(int *count, char *prompt, int *len, char *result);

//utils_funcitions2
void		util_heredoc(char **limit, t_minishell *s_minishell,
				int *count, int *count_command);
int			count_digits(int i);
void		walk_index_quotes(char	*input, int *i);
void		malloc_var_process(t_minishell *s_minishell, char *result,
				int *len, int *i);
void		sig_pipe_error(int f);

#endif