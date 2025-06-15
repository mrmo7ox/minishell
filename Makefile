# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 17:09:10 by moel-oua          #+#    #+#              #
#    Updated: 2025/06/15 15:03:05 by moel-oua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall  -Wextra -Werror
MFLAGS = -lreadline
TSRC = execution/expanding/expand_redic.c execution/expanding/delimiter_exp.c signals/signal.c
USRC = utils/ft_strinstr.c execution/expanding/setup.c execution/expanding/norm_utils.c execution/expanding/expand_hundler.c execution/expanding/expand_hundler2.c execution/expanding/normal_expand.c execution/expanding/more_expand.c  execution/expanding/heredoc_expand.c execution/redirections/more_.c execution/expanding/heredoc_u.c utils/ft_spit_exutils.c utils/more.c utils/ft_getpid.c utils/ft_split_expand.c utils/ft_addstr.c utils/ft_addchr.c utils/ft_strcpy.c  utils/ft_memest.c utils/ft_itoa.c execution/redirections/random.c utils/ft_strdup.c utils/ft_args_split.c utils/ft_vanilla_split.c utils/ft_strdupnofree.c utils/ft_cut.c utils/ft_chrindex.c utils/ft_isalpha.c utils/ft_isalnum.c utils/ft_strip.c  utils/ft_priority.c  utils/ft_minisplit_utils.c utils/ft_strjoin.c  utils/ft_minisplit.c utils/ft_argslen.c utils/ft_putstr_fd.c utils/ft_lstsize.c utils/ft_strstr.c utils/ft_whitespace.c utils/ft_substr.c  utils/ft_chrstr.c utils/ft_lstadd_back.c utils/ft_lstnew.c utils/ft_split.c utils/garbage_collector.c utils/ft_malloc.c utils/ft_strcmp.c utils/ft_atoll.c
ESRC =  execution/redirections/heredoc.c  execution/expanding/expand_utils.c execution/exec/exe_utils.c execution/expanding/remove_qoute.c  execution/redirections/exec_redirec.c execution/exec/exe_cmd.c execution/expanding/split_expand.c execution/expanding/expander.c  execution/builtin/pwd.c execution/builtin/export.c execution/builtin/export_utils2.c execution/builtin/export_utils.c execution/builtin/env.c execution/builtin/echo.c execution/builtin/cd.c execution/builtin/unset.c execution/exec/exec.c execution/builtin/exit.c execution/exec/pipe.c execution/exec/pipe_utils.c execution/exec/pipe_utils2.c  execution/exec/pipe_utils4.c execution/redirections/redirec_utils.c execution/exec/pipe_utils3.c
WSRC =  execution/wildcards/ismatch.c execution/wildcards/wild_utils.c execution/wildcards/wild_utils2.c execution/wildcards/wildcard.c utils/split_wild.c
ENVSRC = ./env/utils.c ./env/utils1.c ./env/env_op.c
PSRC = parsing/synatx_err/redire_more.c parsing/synatx_err/redire_utils.c utils/split_utils.c utils/ft_skip_quates.c parsing/tokenizer/tree.c parsing/synatx_err/syntax_utils.c parsing/synatx_err/qoutes.c parsing/synatx_err/parenthesis.c parsing/synatx_err/redirections.c parsing/synatx_err/syntax_error.c parsing/tokenizer/tokenizer.c  parsing/synatx_err/and_or.c 
SRCS = $(PSRC) $(ESRC) $(ENVSRC) $(USRC) $(TSRC) $(WSRC) ./main.c 
OBJECTS = $(SRCS:%.c=%.o)

NAME = minishell

all: $(NAME)

$(NAME):$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) ${MFLAGS} -o $@

%.o: %.c ./minishell.h 
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	clean 
