/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:50:13 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/22 10:15:29 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	exit_heredoc(t_tk *token, t_container *c, int status)
{
	if (status)
		perror("write");
	close_fds();
	ft_free_env(c->ft_env);
	free_garbage(c->garbage);
	exit(status);
}

static	void	heredoc_eof(t_tk *token, t_container *c)
{
	ft_putstr_fd("warning: here-document ", 2);
	ft_putstr_fd("at line 1 delimited by end-of-file (wanted `ls')\n", 2);
	exit_heredoc(token, c, 0);
	close_fds();
}

void	heredoc_ext(t_tk *token, char *path, t_container *c)
{
	bool	qoutes;
	char	*line;

	line = NULL;
	if (!ft_chrstr('\'', path) && !ft_chrstr('\"', path))
		qoutes = true;
	else
		qoutes = false;
	path = formating(path, c->garbage);
	while (1)
	{
		line = readline("> ");
		if (!line)
			heredoc_eof(token, c);
		ft_add_gc(c->garbage, ft_new_gc_node(line));
		if (!ft_strcmp(path, line))
			break ;
		if (qoutes)
			line = h_expander(line, c);
		if (write(token->in, line, ft_strlen(line)) == -1
			|| write(token->in, "\n", 1) == -1)
			exit_heredoc(token, c, 1);
	}
	exit_heredoc(token, c, 0);
}

bool	ext_exe_redr(t_redic **curr, t_container *c, t_tk *token)
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
		if (!append_files(token, ft_strip('>', tmp->content, c->garbage),
				c))
			return (false);
	}
	else if (tmp->type == HEREDOC)
	{
		if (!heredoc(token, ft_strip('<', tmp->content, c->garbage), c))
			return (false);
	}
	return (true);
}
