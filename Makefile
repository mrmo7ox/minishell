# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 17:09:10 by moel-oua          #+#    #+#              #
#    Updated: 2025/04/29 11:07:27 by ihamani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

       
CC = gcc
CFLAGS = -Wall  -Wextra -Werror -Wno-unused-variable #-fsanitize=leak #-g3 -fsanitize=address 
MFLAGS = -lreadline -lncurses
TSRC = tests/ft_strjoin.c
USRC = utils/ft_lstsize.c utils/minisplit.c utils/ft_strstr.c utils/ft_whitespace.c utils/ft_substr.c  utils/ft_chrstr.c utils/ft_chrcount.c utils/ft_lstadd_back.c utils/ft_lstnew.c utils/ft_split.c utils/garbage_collector.c utils/ft_malloc.c ./utils/ft_strjoin.c ./utils/ft_putstr_fd.c ./utils/ft_argslen.c
ESRC = execution/builtin/pwd.c execution/builtin/export.c execution/builtin/export_utils2.c execution/builtin/export_utils.c execution/builtin/env.c execution/builtin/echo.c execution/builtin/cd.c env/utils.c env/env_op.c 
HSRC = parsing/history/history.c
esrc = ./env/en_op.c ./env/utils.c
PSRC = parsing/tokenizer/tree.c parsing/synatx_err/syntax_utils.c parsing/synatx_err/qoutes.c parsing/synatx_err/parenthesis.c parsing/synatx_err/redirections.c parsing/synatx_err/syntax_error.c parsing/tokenizer/tokenizer.c  parsing/synatx_err/and_or.c parsing/tokenizer/rederctions.c
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
