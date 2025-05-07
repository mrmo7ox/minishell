# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 17:09:10 by moel-oua          #+#    #+#              #
#    Updated: 2025/05/07 09:13:53 by moel-oua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

       
CC = gcc
CFLAGS = -Wall  -Wextra -Werror #-g3 -fsanitize=address  -Wno-unused-variable  -Wno-unused-parameter -Wno-unused-but-set-variable
MFLAGS = -lreadline -lncurses
TSRC = 
USRC = utils/ft_itoa.c execution/redirections/random.c utils/ft_strdup.c utils/ft_args_split.c utils/ft_vanilla_split.c utils/ft_strdupnofree.c utils/ft_cut.c utils/ft_chrindex.c utils/ft_isalpha.c utils/ft_isalnum.c utils/ft_strip.c  utils/ft_priority.c utils/ft_strinstr.c utils/ft_minisplit_utils.c utils/ft_strjoin.c  utils/ft_minisplit.c utils/ft_argslen.c utils/ft_putstr_fd.c utils/ft_lstsize.c utils/ft_strstr.c utils/ft_whitespace.c utils/ft_substr.c  utils/ft_chrstr.c utils/ft_chrcount.c utils/ft_lstadd_back.c utils/ft_lstnew.c utils/ft_split.c utils/garbage_collector.c utils/ft_malloc.c utils/ft_strcmp.c
ESRC = execution/exec/exe_utils.c execution/expanding/remove_qoute.c  execution/redirections/exec_redirec.c execution/exec/exe_cmd.c execution/expanding/split_expand.c execution/expanding/expander.c  execution/builtin/pwd.c execution/builtin/export.c execution/builtin/export_utils2.c execution/builtin/export_utils.c execution/builtin/env.c execution/builtin/echo.c execution/builtin/cd.c env/utils.c env/env_op.c execution/builtin/unset.c execution/exec/exec.c
HSRC = parsing/history/history.c 
esrc = ./env/en_op.c ./env/utils.c
PSRC = parsing/tokenizer/linker.c parsing/synatx_err/parenthesis_utils.c parsing/synatx_err/redire_more.c parsing/synatx_err/redire_utils.c utils/split_utils.c utils/ft_skip_quates.c parsing/tokenizer/tree.c parsing/synatx_err/syntax_utils.c parsing/synatx_err/qoutes.c parsing/synatx_err/parenthesis.c parsing/synatx_err/redirections.c parsing/synatx_err/syntax_error.c parsing/tokenizer/tokenizer.c  parsing/synatx_err/and_or.c 
SRCS = $(PSRC) $(ESRC) $(USRC) $(TSRC) $(HSRC) main.c 
OBJECTS = $(SRCS:%.c=%.o)

NAME = minishell

all: $(NAME)
	make clean
	clear
	./minishell

$(NAME):$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) ${MFLAGS} -o $@

%.o: %.c ./minishell.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	clean 
