/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 09:44:05 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/27 13:40:30 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**gen_arry(char *line, t_container *c)
{
	char	**new;

	new = ft_malloc(sizeof(char *) * 2, c->garbage);
	new[0] = formating(line, c->garbage);
	new[1] = NULL;
	return (new);
}

bool	in_files(t_tk *token, char *path, t_container *c)
{
	char	**tmp;

	tmp = expander(gen_arry(path, c), c);
	if (!tmp || !tmp[0] || (tmp[0] && tmp[1]))
	{
		token->in = -1;
		return (ft_putstr_fd(path, 2), ft_putstr_fd(": ambiguous redirect\n",
				2), false);
	}
	if (token->in)
		close(token->in);
	token->in = open(tmp[0], O_RDONLY);
	if (token->in == -1)
	{
		perror(tmp[0]);
		return (false);
	}
	else
		return (true);
}

bool	out_files(t_tk *token, char *path, t_container *c)
{
	char	**tmp;

	tmp = expander(gen_arry(path, c), c);
	if (!tmp || !tmp[0] || (tmp[0] && tmp[1]))
	{
		token->out = -1;
		return (ft_putstr_fd(path, 2), ft_putstr_fd(": ambiguous redirect\n",
				2), false);
	}
	if (token->out > 0)
		close(token->out);
	token->out = open(tmp[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (token->out == -1)
		return (perror(tmp[0]), false);
	else
		return (true);
}

bool	append_files(t_tk *token, char *path, t_container *c)
{
	char	**tmp;

	tmp = expander(gen_arry(path, c), c);
	if (!tmp || !tmp[0] || (tmp[0] && tmp[1]))
	{
		token->out = -1;
		return (ft_putstr_fd(path, 2), ft_putstr_fd(": ambiguous redirect\n",
				2), false);
	}
	if (token->out > 0)
		close(token->out);
	token->out = open(tmp[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (token->out == -1)
	{
		perror(tmp[0]);
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
	if (token->heredoc > 0)
		close(token->heredoc);
	token->heredoc = open(formating(tmp, c->garbage),
			O_RDWR | O_CREAT | O_APPEND, 0644);
	if (token->heredoc == -1)
		return (perror("heredoc"), false);
	else
	{
		pid = fork();
		if (pid == -1)
			return (token->heredoc = -1, perror("fork"), false);
		else if (!pid)
			heredoc_ext(token, path, c);
		else
		{
			waitpid(pid, &c->status, 0);
			set_status(WEXITSTATUS(c->status), -1);
			if (set_status(0, 0) == 130)
				g_signal = 169;
		}
		if (token->heredoc > 0)
			close(token->heredoc);
		token->heredoc = open(formating(tmp, c->garbage),
				O_RDWR | O_CREAT | O_APPEND, 0644);
		return (unlink(tmp), true);
	}
}

bool	exec_redirec(t_tk *token, t_container *c)
{
	t_redic *curr;

	curr = token->redics;
	token->in = 0;
	token->out = 0;
	while (curr)
	{
		if (!ext_exe_redr(&curr, c, token))
		{
			if (token->heredoc > 0)
				close(token->heredoc);
			return (false);
		}
		curr = curr->next;
	}
	check_iflast(token);
	return (true);
}