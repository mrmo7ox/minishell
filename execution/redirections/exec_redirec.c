/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 09:44:05 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/10 11:56:52 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	in_files(t_tk *token, char *path, t_container *c)
{
	if (token->in)
		close(token->in);
	token->in = open(formating(path, c->garbage), O_RDONLY);
	if (token->in == -1)
		return (false);
	else
	{
		return (true);
	}
}

bool	out_files(t_tk *token, char *path, t_container *c)
{
	if (token->in)
		close(token->in);
	token->in = open(formating(path, c->garbage), O_WRONLY | O_CREAT, 0644);
	if (token->in == -1)
		return (false);
	else
	{
		return (true);
	}
}

bool	append_files(t_tk *token, char *path, t_container *c)
{
	if (token->out)
		close(token->out);
	token->out = open(formating(path, c->garbage),
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (token->out == -1)
		return (false);
	else
	{
		return (true);
	}
}

int	heredoc(t_tk *token, char *path, t_container *c)
{
	char	*tmp;
	char	*line;
	pid_t	pid;
	int		status;
	bool	qoutes;

	status = 0;
	line = NULL;
	tmp = ft_strjoin("/tmp/", ft_itoa(get_random(), c->garbage), c->garbage);
	token->in = open(formating(tmp, c->garbage), O_WRONLY | O_CREAT | O_APPEND,
			0644);
	unlink(tmp);
	if (token->in == -1)
		return (1);
	else
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			if (!ft_chrstr('\'', path) && !ft_chrstr('\"', path))
				qoutes = true;
			else
				qoutes = false;
			path = expander(formating(path, c->garbage), c);
			printf("[%s]\n", path);
			while (1)
			{
				line = readline("heredoc>");
				if (!ft_strcmp(path, line))
					break ;
				if (qoutes)
				{
					line = expander(line, c);
				}
				printf("[%s]\n", line);
				write(token->in, line, ft_strlen(line));
			}
		}
		else
			waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
}

bool	exec_redirec(t_tk *token, t_container *c)
{
	t_redic	*curr;

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
