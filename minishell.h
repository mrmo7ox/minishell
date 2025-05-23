/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/22 10:59:23 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
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
# include <sys/stat.h>
# include <time.h>

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
# define PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

typedef enum e_type
{
	COMMAND,
	OPERATOR,
	PIPE,
	OR,
	AND
}							t_type;

typedef enum e_dollar
{
	INSIDED,
	OUTSIDE,
	INSIDES,
}							t_dollar;

typedef enum e_qoute_type
{
	DQOUTE,
	SQOUTE,
}							t_qtype;

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
	int						out;
	int						in;
	int						fd;
	t_retypes				type;
	struct s_redirection	*next;
	struct s_redirection	*prev;
}							t_redic;

typedef struct s_tokenizer
{
	t_type					type;
	t_redic					*redics;
	char					*token;
	int						in;
	int						out;
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
	t_gc					**garbage;
	t_env					**ft_env;
	t_leaf					**root;
	int						status;
}							t_container;

typedef struct s_qoutes
{
	int						open_index;
	int						close_index;
	t_qtype					type;
	struct s_qoutes			*next;
	struct s_qoutes			*prev;
}							t_qoutes;

typedef struct s_expand
{
	int						start;
	int						end;
	bool					expand;
	struct s_expand			*next;
	struct s_expand			*prev;
}							t_expand;

typedef struct s_list
{
	int						i;
	int						j;
	bool					r;
	bool					e;
	char					*line;
	t_qoutes				**qoutes;
	t_expand				**expand;
	t_env					**env;
	int						status;
}							t_list;

typedef struct s_new_string
{
	int						i;
	int						len;
	size_t					pos;
	char					*holder;
	char					*temp;
	t_expand				*start_end;
}							t_new;

typedef struct s_size
{
	int						i;
	int						len;
	char					*holder;
	char					*temp;
	t_expand				*start_end;
	size_t					new_size;

}							t_size;


void						ft_add_env(t_env **head, t_env *new);
t_env						*ft_new_env(char *name, char *value);
void						env_init(char **env, t_env **ft_env, t_gc **gc);
void						ft_putenv(char *name, char *value, t_env **ft_env);
char						*ft_getenv(char *name, t_env **ft_env);
void						ft_free_env(t_env **ft_env);
char						*env_check_path(t_env **ft_env, int flag);

// builtin
int							cd(char **args, t_gc **gg, t_env **ft_env);
int							echo(char **args, int out);
int							cmd_env(char **args, int out, t_env **env);
int							export(char **args, int out, t_env **ft_env,
								t_gc **gc);
void						export_append(char *name, char *value,
								t_env **ft_env, t_gc **gg);
void						ft_upenv(char *name, char *value, t_env **ft_env);
void						no_env(t_env **ft_env, t_gc **gc);
int							ext_export(char *name, char *value, t_env **ft_env,
								t_gc **gg);
void						export_sort(t_env **ft_env);
char						**export_split(char *str);
bool						check_name_env(char *name, t_env **ft_env);
int							ft_pwd(t_env **ft_env, int out);
int							ft_unset(char **args, t_env **env);
void						clone_env(t_env **ft_env, t_env **tmp, t_gc **gc);
void						shlvl(t_env **ft_env, t_gc **gc);
int							ft_exit(char **args, t_env **ft_env, t_gc **gc,
								int prev);
char						*pwd_update(t_env **ft_env, int flag);
void						no_args_ext(t_env *head, int out);
void						free_d(char **tmp);

// history
void						save_history(void);
void						load_history(void);
// redic
void						ft_add_redic(t_redic **head, t_redic *new);
void						*ft_new_redic_node(t_gc **garbage, char *content);
void						redr_cmd(t_leaf *tmp, t_container *c);

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
int							ft_isalpha(int c);
int							ft_isdigit(int c);
int							ft_isalnum(int c);
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
char						*ft_strip(char chr, char *line, t_gc **garbage);
int							ft_chrindex(char *line, char chr);
char						*ft_cut(char const *s, unsigned int start,
								size_t len);
char						*ft_strdupnofree(const char *source);
void						*ft_memcpy(void *dst, const void *src, size_t n);
char						**ft_args_split(char *str, t_gc **gc, int i, int j);
char						**ft_vanilla_split(char *str, char c, int i, int j);
int							ft_envsize(t_env *head);
char						*ft_itoa(long n, t_gc **garbage);
long						get_random(void);
void						*ft_memset(void *s, int c, size_t n);
t_gc						*ft_new_gc_node(void *content);
void						ft_add_gc(t_gc **head, t_gc *new);
void						free_garbage(t_gc **list);
void						*ft_malloc(size_t size, t_gc **garbage);
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
char						*ft_strcpy(char *dest, const char *src);
int							ft_atoi(const char *str);
long long					ft_atoll(char *str);

// tree
t_leaf						*new_leaf(t_tk *token, t_type type, t_gc **garbage);
t_leaf						*build_ast(t_tk *tokens, t_gc **garbage);

//************************************************************** */
char						*expander(char *line, t_container *c);
void						ft_add_qoute(t_qoutes **head, t_qoutes *new);
void						ft_add_expand(t_expand **head, t_expand *new);
t_qoutes					*ft_new_node(int open, int close, t_qtype type,
								t_gc **garbage);
t_expand					*ft_new_expand(int start, int end, bool expand,
								t_gc **garbage);
t_dollar					is_dollar_in_quotes(t_qoutes **quotes, int index);
t_qoutes					*is_im_quotes(t_qoutes **quotes, int index);
t_expand					*is_index_on_dollar(t_expand **dollars, int index);
void						add_to_quote_list(t_list *u, t_gc **garbage,
								char quote);
void						get_quote_index(t_list *u, t_gc **garbage);
void						add_to_expand_list(t_list *u, bool expand_s,
								t_gc **garbage);
t_list						*get_expand_index(t_list *u, t_gc **garbage);
char						*h_expander(char *line, t_container *c);

//************************************************************** */
// exe
void						exe_cmd(char **args, t_container *c);
void						exit_exe(t_env **ft_env, t_gc **gc, int err);
int							exe_builtin(char **args, t_leaf *root,
								t_container *c);
char						*get_path(char **args, t_env **ft_env, t_gc **gc);
bool						is_builtin(char *str);
char						**dp_env(t_env **ft_env, t_gc **gc);
char						*resolve_path(char **args, t_env **ft_env,
								t_gc **gc);

// redics
bool						exec_redirec(t_tk *token, t_container *c);
void						heredoc_ext(t_tk *token, char *path,
								t_container *c);
bool						ext_exe_redr(t_redic **curr, t_container *c,
								t_tk *token);
bool						in_files(t_tk *token, char *path, t_container *c);
bool						out_files(t_tk *token, char *path, t_container *c);
bool						append_files(t_tk *token, char *path,
								t_container *c);
bool						heredoc(t_tk *token, char *path, t_container *c);

// exec part me
int							execc(t_container *c);

//exe
pid_t						child3(t_container *c, t_leaf **root, int *fd);
void						pipe_err(char *str, t_container *c, int *fds);
void						child2(t_container *c, t_leaf **root, int *fd);
void						exe_pipe(t_leaf *tmp, char **args, t_container *c);
void						ft_dup2(int fd1, int fd2, t_container *c);
void						pipe_handle(t_leaf **root, int *pip,
								t_container *c, int flag);
void						pid_wait(t_container *c, pid_t pid);
void						exevce_fail(char *path, t_container *c);
void						exe_or(t_leaf **root, t_container *c);
void						exe_and(t_leaf **root, t_container *c);
void						close_redr(t_leaf **root);
void						child3_helper(t_leaf *tmp, t_container *c,
								int *p_fd);
void						child2_helper(t_leaf *tmp, t_container *c,
								int *p_fd, int *fds);
void						close_fds(void);
void						child1_helper(t_leaf *tmp, t_container *c,
								int *p_fd);
int							exe_builtin_pipe(char **args, t_leaf *root,
								t_container *c);
void						close_redirec(t_leaf **root, t_container *c);

#endif