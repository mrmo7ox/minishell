/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 09:44:05 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/09 13:56:35 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	in_files(t_redic *redics, char *path, t_gc **garbage)
{
	redics->fd = open(formating(path, garbage), O_RDONLY);
	if (redics->fd == -1)
		return (false);
	else
	{
		return (true);
	}
}

bool	out_files(t_redic *redics, char *path, t_gc **garbage)
{
	redics->fd = open(formating(path, garbage), O_WRONLY | O_CREAT, 0644);
	if (redics->fd == -1)
		return (false);
	else
	{
		return (true);
	}
}

bool	append_files(t_redic *redics, char *path, t_gc **garbage)
{
	redics->fd = open(formating(path, garbage), O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (redics->fd == -1)
		return (false);
	else
	{
		return (true);
	}
}

int	heredoc(t_redic *redics, char *path, t_gc **garbage, t_env **ft_env)
{
	char	*tmp;
	char	*line;
	pid_t	pid;
	int		status;
	bool	qoutes;

	status = 0;
	line = NULL;
	tmp = ft_strjoin("/tmp/", ft_itoa(get_random(), garbage), garbage);
	redics->fd = open(formating(tmp, garbage), O_WRONLY | O_CREAT | O_APPEND,
			0644);
	unlink(tmp);
	if (redics->fd == -1)
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
			path = formating(path, garbage);
			while (ft_strcmp("ls", line))
			{
				line = readline("heredoc>");
				if (qoutes)
				{
					line = expander(line, garbage, ft_env);
					printf("[%s]\n", line);
				}
				write(redics->fd, line, ft_strlen(line));
			}
		}
		else
			waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
}

bool	exec_redirec(t_tk *token, t_gc **garbage, t_env **ft_env)
{
	t_redic	*curr;
	char	**parts;

	(void)garbage;
	(void)parts;
	curr = token->redics;
	token->in = 0;
	token->out = 1;
	while (curr)
	{
		if (curr->type == IN)
		{
			if (!in_files(curr, ft_strip('<', curr->content, garbage), garbage))
				return (false);
		}
		else if (curr->type == OUT)
		{
			if (!out_files(curr, ft_strip('>', curr->content, garbage),
					garbage))
				return (false);
		}
		else if (curr->type == APPEND)
		{
			if (!append_files(curr, ft_strip('>', curr->content, garbage),
					garbage))
				return (false);
		}
		else if (curr->type == HEREDOC)
		{
			if (!heredoc(curr, ft_strip('<', curr->content, garbage), garbage,
					ft_env))
				return (false);
		}
		curr = curr->next;
	}
	return (true);
}
