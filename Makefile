# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 17:09:10 by moel-oua          #+#    #+#              #
#    Updated: 2025/04/15 13:12:20 by moel-oua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

       
CC = gcc
CFLAGS = -Wall  -Wextra -Werror -g3 -fsanitize=address
MFLAGS = -lreadline -lncurses
TSRC = tests/ft_strjoin.c
USRC = utils/ft_lstsize.c utils/minisplit.c utils/ft_strstr.c utils/ft_whitespace.c utils/ft_substr.c  utils/ft_chrstr.c utils/ft_chrcount.c utils/ft_lstadd_back.c utils/ft_lstnew.c utils/ft_split.c utils/garbage_collector.c utils/ft_malloc.c
ESRC =
PSRC = parsing/tokenizer/tree.c parsing/synatx_err/syntax_utils.c parsing/synatx_err/qoutes.c parsing/synatx_err/parenthesis.c parsing/synatx_err/redirections.c parsing/synatx_err/syntax_error.c parsing/tokenizer/tokenizer.c  parsing/synatx_err/and_or.c parsing/tokenizer/rederctions.c
SRCS = $(PSRC) $(ESRC) $(USRC) $(TSRC) main.c 
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
