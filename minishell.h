/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/14 18:34:51 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

# define PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

extern int					g_signal;

typedef enum e_type
{
	COMMAND,
	OPERATOR,
	PIPE,
	OR,
	AND
}							t_type;

typedef enum e_lax
{
	START,
	END,
	NORMAL,
}							t_lax;

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
	int						heredoc;
	int						is_last;
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
	char					*pid;
}							t_c;

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
	t_gc					**garbage;
	t_c						*c;
}							t_list;

typedef struct s_new_string
{
	int						i;
	int						len;
	size_t					pos;
	char					*holder;
	char					*temp;
	t_expand				*start_end;
	t_qoutes				*q;
}							t_new;

typedef struct s_size
{
	int						i;
	int						len;
	char					*holder;
	char					*temp;
	t_expand				*start_end;
	t_qoutes				*q;
	size_t					new_size;

}							t_size;

typedef struct s_arg
{
	char					*arg;
	t_lax					flag;
	struct s_arg			*next;
	struct s_arg			*prev;
}							t_arg;

typedef struct s_wild
{
	char					*arg;
	bool					flag;
	struct s_wild			*next;
	struct s_wild			*prev;
}							t_wild;

typedef struct s_wild_utils2
{
	char					*dir;
	char					**split;
	int						*i;
	t_wild					**head;
	t_c						*c;
	struct dirent			*entry;
}							t_wu;

typedef struct s_as
{
	char					*str;
	int						i;
	int						j;
	int						words;
	int						words_counter;
	char					**res;
	t_gc					**garbage;
}							t_as;

typedef struct s_ismatch
{
	int						i;
	int						j;
	int						star_i;
	int						star_j;
}							t_ismatch;
typedef struct s_expand_hundler
{
	t_expand				*expands;
	t_qoutes				*qoutes;
	char					*line;
	int						*j;
	t_dollar				type;
	t_expand				*data;
	t_c						*c;
}							t_e_h;

void						ft_add_env(t_env **head, t_env *new);
t_env						*ft_new_env(char *name, char *value);
void						env_init(char **env, t_env **ft_env);
void						ft_putenv(char *name, char *value, t_env **ft_env);
char						*ft_getenv(char *name, t_env **ft_env);
void						ft_free_env(t_env **ft_env);
char						*env_check_path(t_env **ft_env, int flag);
int							cd(char **args, t_gc **gg, t_env **ft_env);
int							echo(char **args, int out);
int							cmd_env(char **args, int out, t_env **env);
int							export(char **args, int out, t_env **ft_env,
								t_gc **gc);
void						export_append(char *name, char *value,
								t_env **ft_env, t_gc **gg);
void						ft_upenv(char *name, char *value, t_env **ft_env);
void						no_env(t_env **ft_env);
int							ext_export(char *name, char *value, t_env **ft_env,
								t_gc **gg);
void						export_sort(t_env **ft_env);
char						**export_split(char *str);
bool						check_name_env(char *name, t_env **ft_env);
int							ft_pwd(t_env **ft_env, int out);
int							ft_unset(char **args, t_env **env);
void						clone_env(t_env **ft_env, t_env **tmp);
int							ft_exit(char **args, t_env **ft_env, t_gc **gc,
								int prev);
char						*pwd_update(t_env **ft_env, int flag);
void						no_args_ext(t_env *head, int out);
void						free_d(char **tmp);
void						ft_add_redic(t_redic **head, t_redic *new);
void						*ft_new_redic_node(t_gc **garbage, char *content);
void						redr_cmd(t_leaf *tmp, t_c *c);
bool						tokenizer(t_leaf **root, t_c *c, char *line);
t_tk						*ft_new_tk_node(char *content, t_gc **garbage,
								t_split_utils *utils);
void						ft_add_tk(t_tk **head, t_tk *new);
int							ft_lstsize(t_tk *head);
t_tk						*ft_lstlast(t_tk *root);
bool						and_or(char *line);
bool						syntax_error(char *line);
bool						redir_handler(char *line);
bool						qoutes(char *line);
bool						parenthesis(char *line, int i);
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
bool						has_qoute(char *arg);
void						ft_split(t_tk **res, t_gc **garbage, char *line);
char						*ft_copy(char *src, int len, t_gc **garbage);
int							ft_isalpha(int c);
int							ft_isdigit(int c);
int							ft_isalnum(int c);
t_type						special_cases(char *str);
size_t						args_len(char **args);
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
char						*ft_strip(char chr, char *line, t_gc **garbage);
int							ft_chrindex(char *line, char chr);
char						*ft_cut(char const *s, unsigned int start,
								size_t len);
char						*ft_strdupnofree(const char *source);
void						*ft_memcpy(void *dst, const void *src, size_t n);
char						**ft_args_split(char *str, t_gc **gc);
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
void						ft_minisplit(t_redic **res, t_c *c, t_tk *token,
								t_mini m_utils);
t_retypes					special_cases_redic(char *str);
void						skip_spaces_minisplit(char *line, int *i);
char						*extract_redir(char *line, int *i, int j,
								t_gc **garbage);
char						*extract_file(char *line, int *i, int *j, t_c *c);
int							handle_redirection(t_redic **res, t_c *c,
								char *line, int *i);
char						*ft_strcpy(char *dest, const char *src);
long long					ft_atoll(char *str);
t_leaf						*new_leaf(t_tk *token, t_type type, t_gc **garbage);
t_leaf						*build_ast(t_tk *tokens, t_gc **garbage);
char						**expander(char **args, t_c *c);
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
char						*h_expander(char *line, t_c *c);
void						ft_add_arg(t_arg **head, t_arg *new);
t_arg						*ft_new_arg(char *arg, t_lax flag, t_c *c);
int							ft_args_size(t_arg *head);
char						*ft_addchr(char *str, char chr, t_c *c);
char						*ft_addstr(char *str, char *str2, t_c *c);
char						**ft_expand_split(char *str, t_c *c, int i, int j);
int							ft_args_size_flag(t_arg *head);
char						*get_pid_str(t_c *c);
char						*remove_qoutes(char *arg, t_c *c);
void						exe_cmd(char **args, t_c *c);
void						exit_exe(t_env **ft_env, t_gc **gc, int err);
int							exe_builtin(char **args, t_leaf *root, t_c *c);
char						*get_path(char **args, t_env **ft_env, t_gc **gc);
bool						is_builtin(char *str);
char						**dp_env(t_env **ft_env, t_gc **gc);
char						*resolve_path(char **args, t_env **ft_env,
								t_gc **gc);
bool						exec_redirec(t_tk *token, t_c *c);
void						heredoc_ext(t_tk *token, char *path, t_c *c);
bool						ext_exe_redr(t_redic **curr, t_c *c, t_tk *token);
bool						in_files(t_tk *token, char *path, t_c *c);
bool						out_files(t_tk *token, char *path, t_c *c);
bool						append_files(t_tk *token, char *path, t_c *c);
bool						heredoc(t_tk *token, char *path, t_c *c);
bool						check_redr_file(char *str);
int							execc(t_c *c);
pid_t						child3(t_c *c, t_leaf **root, int *fd);
void						pipe_err(char *str, t_c *c, int *fds);
void						child2(t_c *c, t_leaf **root, int *fd);
void						exe_pipe(char **args, t_c *c);
void						pipe_handle(t_leaf **root, int *pip, t_c *c,
								int flag);
bool						exe_cmd_hundler(t_leaf *node, t_c *c);
void						pid_wait(t_c *c, pid_t pid);
void						exevce_fail(char *path, t_c *c);
void						close_redr(t_leaf **root);
void						child3_helper(t_leaf *tmp, t_c *c, int *p_fd);
void						child2_helper(t_leaf *tmp, t_c *c, int *p_fd,
								int *fds);
void						child1_helper(t_leaf *tmp, t_c *c, int *p_fd);
int							exe_builtin_pipe(char **args, t_c *c);
void						close_heredoc(t_leaf **root, t_c *c);
void						exec_heredoc(t_tk *token, t_c *c);
void						check_iflast(t_tk *token);
void						close_fds(t_leaf *tmp, int *fds, int *p_fd);
void						redr_cmd_helper(t_leaf *tmp, t_c *c);
void						child2_pipe(t_leaf *tmp, t_c *c, int *fds,
								int *p_fd);
void						cmd_no_args(t_leaf *tmp, t_c *c);
void						path_check_pro(char **args);
void						handler(int sig);
int							set_status(int new_status, int flag);
void						handle_signal_exe(int status);
void						handle_signal_pip(int tmp, int status);
void						ft_add_wild(t_wild **head, t_wild *new);
t_wild						*ft_new_wild(char *arg, bool flag, t_c *c);
int							ft_wildsize(t_wild *head);
char						**wildcards(char **args, t_c *c);
void						recursive_wild(t_wu *wu);
char						**ft_wild_split(char *str, t_c *c, int i, int j);
bool						ismatch(char *s, char *p);
bool						current_dir(char *line);
int							is_dir(char *line);
void						skip_hit(int *i, char *str);
void						not_hit(int *i, char *str);
void						skip_it(char *str, int *i);
bool						more_things(t_as *u);
char						**gen_arry(char *line, t_gc **garbage);
bool						find_case_b(t_size *u, t_list *utils);
bool						find_case(t_new *s, char *new, char *line,
								t_list *utils);
bool						check_f(t_tk *token, char *path, t_c *c);
void						convert(t_arg **args, char **new);
bool						has_dollar(char *arg);
bool						has_qoute(char *arg);
char						*expand(char *arg, char *next, t_c *c);
char						**convert_(char *line, t_c *c);
char						**convert_flag(t_arg **args, t_c *c);
char						**convert_to_array(t_arg **head, t_c *c);
t_list						*init_list(char *arg, t_c *c);
char						**hundler(char **args, t_c *c, int i);
char						*decide(char **array, int i);
void						handle_quotes_only(char *arg, t_c *c, t_arg **head);
char						*handle_dollar_in_quotes(char *arg, t_c *c);
int							process_dollar_expansion(char *arg, int j, t_c *c,
								char **line);
bool						ft_strinstr(char *haystack, char *needle);
void						env_init_helper(char *name, char *value,
								t_env **ft_env);
bool						check_amb(char *new);
void						init_pwd(t_env **ft_env);
char						*del_exp(char *line, t_c *c);
void						merge_sorting(t_wild **head, t_c *c);
char						*redc_expander(char *line, t_c *c);

#endif