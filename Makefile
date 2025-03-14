# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 17:09:10 by moel-oua          #+#    #+#              #
#    Updated: 2025/03/14 12:40:30 by moel-oua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

       
CC = cc
CFLAGS = -Wall -Werror -Wextra
MFLAGS = -lreadline -lncurses
USRC = utils/ft_lstadd_back.c utils/ft_lstnew.c utils/ft_split.c utils/garbage_collector.c
ESRC =
PSRC = parsing/tokenizer/tokenizer.c 
SRCS = $(PSRC) $(ESRC) $(USRC) main.c 
OBJECTS = $(SRCS:%.c=%.o)

NAME = minishell

all: $(NAME)
	make clean
	clear
	valgrind ./minishell

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
