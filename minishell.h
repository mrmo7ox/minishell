/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/25 21:37:32 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

typedef enum
{
	COMMAND,
	OPERATOR,
} e_type;

typedef enum
{
	IN,
	OUT,
	APPEND,
	HEREDOC,
	CMD,
} e_redic;

typedef struct s_garbage
{
	void *addr;
	void *next;
} t_gc;

typedef struct s_redirection
{
	char *content;
	e_redic type;
	struct s_redirection *next;
	struct s_redirection *prev;
} t_redic;

typedef struct s_tokenizer
{
	e_type type;
	t_redic *redics;
	char *token;
	int priority;
	int index;
	struct s_tokenizer *next;
	struct s_tokenizer *prev;
} t_tk;

typedef struct leaf
{
	e_type type;
	t_tk *token;
	struct leaf *left;
	struct leaf *right;
} t_leaf;

// history
// remove when want to push this is for the history cmds
#define HISTORY_FILE ".command_history"
#define MAX_HISTORY_LENGTH 1000
void save_history();
void load_history();
const char *token_type_to_str(e_type type);

// redic
void ft_add_redic(t_redic **head, t_redic *new);
void *ft_new_redic_node(t_gc **garbage, char *content);

// tokenizer
bool tokenizer(t_gc **garbage, char *line);
t_tk *ft_new_tk_node(char *content, int priority, t_gc **garbage, int index, e_type type);
void ft_add_tk(t_tk **head, t_tk *new);
int ft_lstsize(t_tk *head);
t_tk *ft_lstlast(t_tk *root);

// syntax_error
bool and_or(char *line);
bool syntax_error(char *line);
bool redir_handler(char *line);
bool qoutes(char *line);
bool parenthesis(char *line, int open_count, int i, int j);
char *formating(char *line, t_gc **gg);
int mod_chrstr(char chr, char *str);
void skip(char *line, int *i);

e_type special_cases(char *str);
e_redic special_cases_redic(char *str);
t_redic *ft_lstlast_redic(t_redic *root);

// utils
void ft_split(t_tk **res, t_gc **garbage, char *line, int i, int j);
int ft_chrcount(char *str, char c);
bool ft_chrstr(char chr, char *str);
void *ft_memcpy(void *dst, const void *src, size_t n);
bool ft_whitespaces(char chr);
bool ft_strstr(char *line, char *sp);
void skip(char *line, int *i);

void ft_skip_wspaces(char *line, int *i);
char *ft_substr(char const *s, unsigned int start, size_t len, t_gc **gg);
int ft_strcmp(const char *s1, const char *s2);

// garbage collector
t_gc *ft_new_gc_node(void *content);
void ft_add_gc(t_gc **head, t_gc *new);
void free_garbage(t_gc **list);
void *ft_malloc(size_t size, t_gc **garbage);

// for testing
size_t ft_strlen(const char *s);
char *ft_strjoin(char const *s1, char const *s2);
void *ft_memcpy(void *dst, const void *src, size_t n);
char *ft_strdup(const char *source);
void ft_minisplit(t_redic **res, t_gc **garbage, t_tk *token, char *line, int i, int j);
// tree
t_leaf *new_leaf(t_tk *token, e_type type);

#endif