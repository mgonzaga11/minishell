# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/20 17:13:45 by izanoni           #+#    #+#              #
#    Updated: 2024/08/01 17:55:04 by mgonzaga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror -g3 -I$(LIBFT)
RM = rm -f

LIBFT = ./libft
SRC_PATH = ./src/
FILES = $(addprefix $(SRC_PATH), $(addsuffix .c, bt_cd\
			bt_env \
			bt_export \
			bt_unset \
			error \
			free_all \
			bt_echo \
			bt_pwd \
			check_input \
			exec_command \
			exec_command2 \
			init_minishell \
			redirect \
			expand_var \
			expand_var2 \
			t_list_functions \
			signals \
			heredoc \
			norme_prompt\
			check_command\
			envp_funcitions\
			utils_functions\
			utils_functions2\
			bt_exit\
			utils_bt_or_exec\
			main\
			more_command\
			handle_path\
			aux_children\
			utils_export))
			 
OBJ = $(FILES:%.c=%.o)			

all: libs $(NAME) leak_readline
	
$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT)/libft.a -l readline -o $(NAME)

libs:
	@make -C $(LIBFT) --silent

v: all
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --trace-children-skip='*/bin/*,*/sbin/*' --keep-debuginfo=yes \
	--suppressions=leak_readline --track-fds=yes ./$(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ -I .

clean:
	@make clean -C $(LIBFT)
	@$(RM)  $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT)
	@$(RM) $(NAME) leak_readline

re: fclean all

leak_readline:
	@printf "{\n" > leak_readline
	@printf "   ignore_libreadline_leaks\n" >> leak_readline
	@printf "    Memcheck:Leak\n" >> leak_readline
	@printf "    ...\n" >> leak_readline
	@printf "    obj:*/libreadline.so.*\n" >> leak_readline
	@printf "}\n" >> leak_readline

.PHONY: all clean fclean re libs v