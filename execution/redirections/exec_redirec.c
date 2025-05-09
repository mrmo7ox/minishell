/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 09:44:05 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/09 15:12:18 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	in_files(t_tk *token, char *path, t_gc **garbage)
{
	if (token->in)
		close(token->in);
	token->in = open(formating(path, garbage), O_RDONLY);
	if (token->in == -1)
		return (false);
	else
	{
		return (true);
	}
}

bool	out_files(t_tk *token, char *path, t_gc **garbage)
{
	if (token->in)
		close(token->in);
	token->in = open(formating(path, garbage), O_WRONLY | O_CREAT, 0644);
	if (token->in == -1)
		return (false);
	else
	{
		return (true);
	}
}

bool	append_files(t_tk *token, char *path, t_gc **garbage)
{
	if (token->out)
		close(token->out);
	token->out = open(formating(path, garbage), O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (token->out == -1)
		return (false);
	else
	{
		return (true);
	}
}

int	heredoc(t_tk *token, char *path, t_gc **garbage, t_env **ft_env)
{
	char	*tmp;
	char	*line;
	pid_t	pid;
	int		status;
	bool	qoutes;
	int		o[2];

	status = 0;
	line = NULL;
	tmp = ft_strjoin("/tmp/", ft_itoa(get_random(), garbage), garbage);
	token->in = open(formating(tmp, garbage), O_WRONLY | O_CREAT | O_APPEND,
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
			printf("[%d]\n", qoutes);
			o[0] = 1;
			o[1] = 0;
			path = expander(formating(path, garbage), garbage, ft_env, o);
			printf("[%s]\n", path);
			while (1)
			{
				line = readline("heredoc>");
				if (!ft_strcmp(path, line))
					break ;
				if (qoutes)
				{
					o[0] = 0;
					o[1] = 1;
					line = expander(line, garbage, ft_env, o);
					printf("[%s]\n", line);
				}
				write(token->in, line, ft_strlen(line));
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
	token->out = 0;
	while (curr)
	{
		if (curr->type == IN)
		{
			if (!in_files(token, ft_strip('<', curr->content, garbage),
					garbage))
				return (false);
		}
		else if (curr->type == OUT)
		{
			if (!out_files(token, ft_strip('>', curr->content, garbage),
					garbage))
				return (false);
		}
		else if (curr->type == APPEND)
		{
			if (!append_files(token, ft_strip('>', curr->content, garbage),
					garbage))
				return (false);
		}
		else if (curr->type == HEREDOC)
		{
			if (!heredoc(token, ft_strip('<', curr->content, garbage), garbage,
					ft_env))
				return (false);
		}
		curr = curr->next;
	}
	return (true);
}
