/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 09:44:05 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/11 10:07:31 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool in_files(t_tk *token, char *path, t_container *c)
{
	char *tmp;

	tmp = expander(formating(path, c->garbage), c);
	if (token->in)
		close(token->in);
	token->in = open(tmp, O_RDONLY);
	if (token->in == -1)
	{
		perror(tmp);
		return (false);
	}
	else
	{
		return (true);
	}
}

bool out_files(t_tk *token, char *path, t_container *c)
{
	char *tmp;

	tmp = expander(formating(path, c->garbage), c);
	if (token->out)
		close(token->out);
	token->out = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (token->out == -1)
	{
		perror(tmp);
		return (false);
	}
	else
	{
		return (true);
	}
}

bool append_files(t_tk *token, char *path, t_container *c)
{
	char *tmp;

	tmp = expander(formating(path, c->garbage), c);
	if (token->in)
		close(token->in);
	token->in = open(tmp,
					 O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (token->in == -1)
	{
		perror(tmp);
		return (false);
	}
	else
		return (true);
}

bool heredoc(t_tk *token, char *path, t_container *c)
{
	char *tmp;
	char *line;
	pid_t pid;
	bool qoutes;

	line = NULL;
	tmp = ft_strjoin("/tmp/", ft_itoa(get_random(), c->garbage), c->garbage);
	token->in = open(formating(tmp, c->garbage), O_RDWR | O_CREAT | O_APPEND,
					 0644);
	if (token->in == -1)
	{
		perror("heredoc");
		return (false);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (false);
		}
		else if (pid == 0)
		{
			if (!ft_chrstr('\'', path) && !ft_chrstr('\"', path))
				qoutes = true;
			else
				qoutes = false;
			path = expander(formating(path, c->garbage), c);
			while (1)
			{
				line = readline("> ");
				if (!ft_strcmp(path, line))
					break;
				if (qoutes)
					line = h_expander(line, c);
				if (write(token->in, line, ft_strlen(line)) == -1)
					perror("write");
			}
		}
		else
			waitpid(pid, &c->status, 0);
		close(token->in);
		token->in = open(formating(tmp, c->garbage), O_RDWR | O_CREAT | O_APPEND, 0644);
		unlink(tmp);
		return (true);
	}
}

bool exec_redirec(t_tk *token, t_container *c)
{
	t_redic *curr;

	curr = token->redics;
	token->in = 0;
	token->out = 0;
	while (curr)
	{
		if (curr->type == IN)
		{
			if (!in_files(token, ft_strip('<', curr->content, c->garbage), c))
				return (false);
		}
		else if (curr->type == OUT)
		{
			if (!out_files(token, ft_strip('>', curr->content, c->garbage), c))
				return (false);
		}
		else if (curr->type == APPEND)
		{
			if (!append_files(token, ft_strip('>', curr->content, c->garbage),
							  c))
				return (false);
		}
		else if (curr->type == HEREDOC)
		{
			if (!heredoc(token, ft_strip('<', curr->content, c->garbage), c))
				return (false);
		}
		curr = curr->next;
	}
	return (true);
}
