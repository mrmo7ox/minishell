/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/26 14:04:27 by ihamani          ###   ########.fr       */
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
# include <limits.h>
# include <sys/wait.h>
# include "./env/env.h"
# include "./execution/builtin/builtins.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


typedef struct s_garbage
{
	void	*addr;
	void	*next;
}			t_gc;

typedef struct s_tokenizer
{
	char				*token;
	int					priority;
	char				*op;
	int					index;
	struct s_tokenizer	*next;
	struct s_tokenizer	*prev;
}						t_tk;

typedef struct s_redirections
{
	char					*content;
	char					*op;
	int						index;
	struct s_redirections	*next;
	struct s_redirections	*prev;
}							t_redirections;

typedef struct s_ready
{
	char			**tokens;
	int				priority;
	struct s_ready	*next;
	struct s_ready	*prev;
}						t_ready;

typedef struct s_tree
{
	char			*content;
	int				priority;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*prev;
}			t_node;

typedef struct s_redr
{
	char	*type;
	char	*file_name;
	int		here_doc;
	void	*next;
}			t_redr; 

// history
//remove when want to push this is for the history cmds
#define HISTORY_FILE ".command_history"
#define MAX_HISTORY_LENGTH 1000 
void save_history();
void load_history();

// tokenizer
bool	tokenizer(t_gc **garbage, char *line, t_node **root);
t_tk	*ft_new_tk_node(char *content, int priority, t_gc **garbage, int index);
void	ft_add_tk(t_tk **head, t_tk *new);
int		ft_lstsize(t_tk *head);

// groups
void	ft_add_ready(t_ready **head, t_ready *new);
t_ready	*ft_new_ready(char **content, int priority, t_gc **garbage);
void    create_groups(t_tk **tokens, t_ready **groups, t_gc **garbage);

//rederction
void	rederction(char *line, t_redr **redr, t_gc **gg);
t_redirections	*ft_new_redirection(char *content, char *op , int team);
void	ft_add_t_redirections(t_redirections **head, t_redirections *new);
//tree
t_node	*ft_newtree(char *content);
void	ft_addtree_node(t_node **node, t_node *left, t_node *right);


// syntax_error
bool	and_or(char *line);
bool	syntax_error(char *line);
bool	redir_handler(char *line);
bool	qoutes(char *line);
bool	parenthesis(char *line, int open_count, int i, int j);
char	*formating(char *line, t_gc **gg);
int		mod_chrstr(char chr, char *str);
void	skip(char *line, int *i);
bool	special_cases(char *str);

// utils
void	ft_split(t_tk **res, t_gc **garbage, char *line, int i, int j);
int		ft_chrcount(char *str, char c);
bool	ft_chrstr(char chr, char *str);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
bool	ft_whitespaces(char chr);
bool	ft_strstr(char *line, char *sp);
void	skip(char *line, int *i);
char	**ft_minisplit(char *str, char c, int i, int j);
void	ft_skip_wspaces(char *line, int *i);
char	*ft_substr(char const *s, unsigned int start, size_t len, t_gc **gg);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *str, int fd);
size_t	args_len(char **args);

// garbage collector
t_gc	*ft_new_gc_node(void *content);
void	ft_add_gc(t_gc **head, t_gc *new);
void	free_garbage(t_gc **list);
void	*ft_malloc(size_t size, t_gc **garbage);

// for testing 
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *source);

#endif