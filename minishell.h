/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/13 15:22:52 by moel-oua         ###   ########.fr       */
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
# include <signal.h>
# include <unistd.h>

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

typedef struct s_tree
{
	char	**content;
	int		priority;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*prev;
}			t_node;

// tokenizer
bool	tokenizer(t_gc **garbage, t_tk **tokens, char *line, t_node **root);
t_tk	*ft_new_tk_node(void *content, void *token);
void	ft_add_tk(t_tk **head, t_tk *new);

//tree
t_node	*ft_newtree(char **content);
void	ft_addtree_node(t_node **node, t_node *left, t_node *right);


// syntax_error
bool	and_or(char *line);
bool	syntax_error(char *line);
bool	redir_handler(char *line);
bool	qoutes(char *line);
bool	parenthesis(char *line, int open_count, int i, int j);
char	*formating(char *line);
int		mod_chrstr(char chr, char *str);
void	skip(char *line, int *i);

// utils
char	**ft_split(char *line, int i, int j);
int		ft_chrcount(char *str, char c);
bool	ft_chrstr(char chr, char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
bool	ft_whitespaces(char chr);
bool	ft_strstr(char *line, char *sp);
void	skip(char *line, int *i);
char	**ft_minisplit(char *str, char c, int i, int j);

// garbage collector
t_gc	*ft_new_gc_node(void *content);
void	ft_add_gc(t_gc **head, t_gc *new);
void	free_garbage(t_gc **list);

// for testing 
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *source);

#endif