/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nero <nero@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/03/17 17:30:47 by nero             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

typedef struct s_garbage
{
	void	*addr;
	void	*next;
}			t_gc;

typedef struct s_tokenizer
{
	void	*str;
	void	*token;
	void	*next;
	void	*prev;
}			t_tk;

// tokenizer
bool	tokenizer(t_gc **garbage, t_tk **tokens, char *line);
t_tk	*ft_new_tk_node(void *content, void *token);
void	ft_add_tk(t_tk **head, t_tk *new);

// syntax_error
bool	and_or(char *line);
bool	syntax_error(char *line);
bool	redir_handler(char *line);
bool	qoutes(char *line);
bool	parenthesis(char *line, int *i, int depth);
void 	skip_qoutes(char *line, int *i);

// utils
char	**ft_split(char *str, char *sap, int i, int j);
int		ft_chrcount(char *str, char c);
bool	ft_chrstr(char chr, char *str);


// garbage collector
bool	add_split_gc(t_gc **head ,char **res);
t_gc	*ft_new_gc_node(void *content);
void	ft_add_gc(t_gc **head, t_gc *new);
void	free_garbage(t_gc **list);





// for testing 
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *source);

#endif