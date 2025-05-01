/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/01 12:01:16 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define HISTORY_FILE ".command_history"
# define MAX_HISTORY_LENGTH 1000
# define KNRM "\x1B[0m"
# define KRED "\x1B[31m"
# define KGRN "\x1B[32m"
# define KYEL "\x1B[33m"
# define KBLU "\x1B[34m"
# define KMAG "\x1B[35m"
# define KCYN "\x1B[36m"
# define KWHT "\x1B[37m"

typedef enum e_type
{
	COMMAND,
	OPERATOR,
	PIPE,
	OR,
	AND
}							t_type;

typedef enum e_redic
{
	IN,
	OUT,
	APPEND,
	HEREDOC,
	CMD,
}							t_retypes;

typedef struct s_garbage
{
	void					*addr;
	void					*next;
}							t_gc;

typedef struct s_redirection
{
	char					*content;
	t_retypes				type;
	struct s_redirection	*next;
	struct s_redirection	*prev;
}							t_redic;

typedef struct s_tokenizer
{
	t_type					type;
	t_redic					*redics;
	char					*token;
	int						priority;
	int						subshell;
	int						index;
	struct s_tokenizer		*next;
	struct s_tokenizer		*prev;
}							t_tk;

typedef struct leaf
{
	t_type					type;
	t_tk					*token;
	struct leaf				*left;
	struct leaf				*right;
}							t_leaf;

typedef struct s_split_utils
{
	int						i;
	int						j;
	int						subshell;
	int						priority;
	int						index;
	t_type					type;
}							t_split_utils;

typedef struct s_mini
{
	int						i;
	int						j;
	char					*line;
	t_retypes				type;
}							t_mini;

typedef struct s_expander
{
	char					*target;
	bool					expandable;
	int						start;
	int						end;
}							t_expander;

// env
typedef struct s_env
{
	char					*name;
	char					*value;
	void					*next;
}							t_env;

typedef struct s_container
{
	char					*line;
	t_gc					*garbage;
	t_env					*ft_env;
	t_leaf					*root;
}							t_container;

void						ft_add_env(t_env **head, t_env *new);
t_env						*ft_new_env(char *name, char *value);
void						env_init(char **env, t_env **ft_env, t_gc **gc);
void						ft_putenv(char *name, char *value, t_env **ft_env);
char						*ft_getenv(char *name, t_env **ft_env);

// builtin
void						cd(char **args, t_gc **gg);
void						echo(char **args);
void						cmd_env(char **args, t_env **env);
void						export(char **args, t_env **ft_env, t_gc **gg);
void						export_append(char *name, char *value,
								t_env **ft_env, t_gc **gg);
void						ft_upenv(char *name, char *value, t_env **ft_env);
void						ext_export(char *name, char *value, t_env **ft_env,
								t_gc **gg);
void						export_sort(t_env **ft_env);
char						**export_split(char *str, t_gc **gg);
bool						check_name_env(char *name, t_env **ft_env);
char						*ft_pwd(char **args, t_gc **gg);
void						ft_unset(char **args, t_env **env);
void						clone_env(t_env **ft_env, t_env **tmp, t_gc **gc);

// history
void						save_history(void);
void						load_history(void);
// redic
void						ft_add_redic(t_redic **head, t_redic *new);
void						*ft_new_redic_node(t_gc **garbage, char *content);

// tokenizer
bool						tokenizer(t_leaf **root, t_gc **garbage,
								char *line);
t_tk						*ft_new_tk_node(char *content, t_gc **garbage,
								t_split_utils *utils);
void						ft_add_tk(t_tk **head, t_tk *new);
int							ft_lstsize(t_tk *head);
t_tk						*ft_lstlast(t_tk *root);

// syntax_error
bool						and_or(char *line);
bool						syntax_error(char *line);
bool						redir_handler(char *line);
bool						qoutes(char *line);
bool						parenthesis(char *line, int open_count, int i,
								int j);
char						*formating(char *line, t_gc **gg);
int							mod_chrstr(char chr, char *str);
void						skip(char *line, int *i);
t_type						special_cases(char *str);
t_retypes					special_cases_redic(char *str);
t_redic						*ft_lstlast_redic(t_redic *root);
void						skip_double_quote(char **line);
void						skip_single_quote(char **line);
void						skip_quotes_check(char **line);
void						update_count_and_check(char **line, int *count);
bool						check_count_validity(int count, char *line);
bool						correct_count(char *line);
bool						check_op_conflict(char **line, char oldchr);
bool						correct_format(char *line);
void						move_next(char *line, int *i);

// utils
void						ft_split(t_tk **res, t_gc **garbage, char *line);
char						*ft_copy(char *src, int len, t_gc **garbage);
t_type						special_cases(char *str);
size_t						args_len(char **args);
int							ft_chrcount(char *str, char c);
bool						ft_chrstr(char chr, char *str);
void						*ft_memcpy(void *dst, const void *src, size_t n);
bool						ft_whitespaces(char chr);
bool						ft_strstr(char *line, char *sp);
void						skip(char *line, int *i);
void						ft_putstr_fd(char *str, int fd);
void						ft_skip_wspaces(char *line, int *i);
char						*ft_substr(char const *s, unsigned int start,
								size_t len, t_gc **gg);
int							ft_strcmp(const char *s1, const char *s2);
int							ft_skip_quates(int *i, char *line);
int							ft_priority(char *token);
bool						ft_strinstr(char *haystack, char *needle);

// garbage collector
t_gc						*ft_new_gc_node(void *content);
void						ft_add_gc(t_gc **head, t_gc *new);
void						free_garbage(t_gc **list);
void						*ft_malloc(size_t size, t_gc **garbage);

// for testing
size_t						ft_strlen(const char *s);
char						*ft_strjoin(char const *s1, char const *s2,
								t_gc **garbage);
void						*ft_memcpy(void *dst, const void *src, size_t n);
char						*ft_strdup(const char *source, t_gc **garbage);
void						ft_minisplit(t_redic **res, t_gc **garbage,
								t_tk *token, t_mini m_utils);
t_retypes					special_cases_redic(char *str);
void						skip_spaces_minisplit(char *line, int *i);
char						*extract_redir(char *line, int *i, int j,
								t_gc **garbage);
char						*extract_file(char *line, int *i, int *j,
								t_gc **garbage);
int							handle_redirection(t_redic **res, t_gc **garbage,
								char *line, int *i);

// tree
t_leaf						*new_leaf(t_tk *token, t_type type, t_gc **garbage);
t_leaf						*build_ast(t_tk *tokens, t_gc **garbage);
void						linker(t_leaf **root, void (*applyme)(t_tk *token),
								t_gc **garbage);

// expanding
void						expander(t_tk *token);
t_expander					*split_expand(char *line, t_gc **garbage);

#endif