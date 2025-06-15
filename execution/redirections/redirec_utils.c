/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:50:13 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/14 18:09:37 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	exit_heredoc(t_c *c, int status)
{
	if (status && g_signal != 169)
		perror("write");
	ft_free_env(c->ft_env);
	close_heredoc(c->root, c);
	free_garbage(c->garbage);
	exit(status);
}

static void	heredoc_eof(t_c *c)
{
	if (g_signal != 169)
	{
		ft_putstr_fd("warning: here-document ", 2);
		ft_putstr_fd("delimited by end-of-file\n", 2);
		exit_heredoc(c, 0);
	}
	else if (g_signal == 169)
		exit_heredoc(c, 130);
}

void	heredoc_ext(t_tk *token, char *path, t_c *c)
{
	bool	qoutes;
	char	*line;

	line = NULL;
	if (!ft_chrstr('\'', path) && !ft_chrstr('\"', path))
		qoutes = true;
	else
		qoutes = false;
	path = formating(path, c->garbage);
	g_signal = 69;
	while (1)
	{
		line = readline("> ");
		if (!line || g_signal == 169)
			heredoc_eof(c);
		ft_add_gc(c->garbage, ft_new_gc_node(line));
		if (!ft_strcmp(del_exp(path, c), line))
			break ;
		if (qoutes)
			line = h_expander(line, c);
		if (write(token->heredoc, line, ft_strlen(line)) == -1
			|| write(token->heredoc, "\n", 1) == -1)
			exit_heredoc(c, 1);
	}
	exit_heredoc(c, 0);
}

bool	ext_exe_redr(t_redic **curr, t_c *c, t_tk *token)
{
	t_redic	*tmp;

	tmp = *curr;
	if (tmp->type == IN)
	{
		if (!in_files(token, ft_strip('<', tmp->content, c->garbage), c))
			return (false);
	}
	else if (tmp->type == OUT)
	{
		if (!out_files(token, ft_strip('>', tmp->content, c->garbage), c))
			return (false);
	}
	else if (tmp->type == APPEND)
	{
		if (!append_files(token, ft_strip('>', tmp->content, c->garbage), c))
			return (false);
	}
	return (true);
}

bool	check_redr_file(char *str)
{
	int	i;

	i = 0;
	while (ft_whitespaces(str[i]))
		i++;
	while (str[i] && str[i] == '$')
		i++;
	if (!str[i])
		return (false);
	return (true);
}
