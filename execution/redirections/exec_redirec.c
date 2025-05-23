/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 09:44:05 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/22 10:32:26 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	in_files(t_tk *token, char *path, t_container *c)
{
	char	*tmp;

	tmp = expander(formating(path, c->garbage), c);
	if (!tmp[0])
	{
		token->in = -1;
		return (ft_putstr_fd(path, 2),
			ft_putstr_fd(": ambiguous redirect\n", 2), false);
	}
	if (token->in)
		close(token->in);
	token->in = open(tmp, O_RDONLY);
	if (token->in == -1)
	{
		perror(tmp);
		return (false);
	}
	else
		return (true);
}

bool	out_files(t_tk *token, char *path, t_container *c)
{
	char	*tmp;

	tmp = expander(formating(path, c->garbage), c);
	if (!tmp[0])
	{
		token->out = -1;
		return (ft_putstr_fd(path, 2),
			ft_putstr_fd(": ambiguous redirect\n", 2), false);
	}
	if (token->out > 0)
		close(token->out);
	token->out = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (token->out == -1)
		return (perror(tmp), false);
	else
		return (true);
}

bool	append_files(t_tk *token, char *path, t_container *c)
{
	char	*tmp;

	tmp = expander(formating(path, c->garbage), c);
	if (!tmp[0])
	{
		token->out = -1;
		return (ft_putstr_fd(path, 2),
			ft_putstr_fd(": ambiguous redirect\n", 2), false);
	}
	if (token->out > 0)
		close(token->out);
	token->out = open(tmp,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (token->out == -1)
	{
		perror(tmp);
		return (false);
	}
	else
		return (true);
}

bool	heredoc(t_tk *token, char *path, t_container *c)
{
	char	*tmp;
	pid_t	pid;

	tmp = ft_strjoin("/tmp/", ft_itoa(get_random(), c->garbage), c->garbage);
	if (token->in > 0)
		close(token->in);
	token->in = open(formating(tmp, c->garbage), O_RDWR | O_CREAT | O_APPEND,
			0644);
	if (token->in == -1)
		return (close(token->in), perror("heredoc"), false);
	else
	{
		pid = fork();
		if (pid == -1)
			return (token->in = -1, perror("fork"), false);
		else if (!pid)
			heredoc_ext(token, path, c);
		else
		{
			waitpid(pid, &c->status, 0);
			c->status = WEXITSTATUS(c->status);
		}
		if (token->in > 0)
			close(token->in);
		token->in = open(formating(tmp, c->garbage),
				O_RDWR | O_CREAT | O_APPEND, 0644);
		return (unlink(tmp), true);
	}
}

bool	exec_redirec(t_tk *token, t_container *c)
{
	t_redic		*curr;

	curr = token->redics;
	token->in = 0;
	token->out = 0;
	while (curr)
	{
		if (!ext_exe_redr(&curr, c, token))
			return (false);
		curr = curr->next;
	}
	return (true);
}
