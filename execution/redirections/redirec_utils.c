/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:50:13 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/13 15:24:08 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	exit_heredoc(t_tk *token, t_container *c, int status)
{
	close(token->in);
	ft_free_env(c->ft_env);
	free_garbage(c->garbage);
	exit(status);
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
	path = expander(formating(path, c->garbage), c);
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(path, line))
			break ;
		if (qoutes)
			line = h_expander(line, c);
		if (write(token->in, line, ft_strlen(line)) == -1
			|| write(token->in, "\n", 1) == -1)
		{
			perror("write");
			exit_heredoc(token, c, 1);
		}
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
