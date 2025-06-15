/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:02:33 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/14 11:37:56 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	hd_helper(char *tmp, t_tk *token, int flag, t_c *c)
{
	if (flag == 1)
	{
		if (token->heredoc != -1)
		{
			if (token->heredoc > 0)
				close(token->heredoc);
			token->heredoc = open(formating(tmp, c->garbage),
					O_RDWR | O_CREAT | O_APPEND, 0644);
		}
	}
	else if (flag == 2)
	{
		write(1, "\n", 1);
		close_heredoc(c->root, c);
		token->heredoc = -1;
		g_signal = 169;
	}
	else if (!flag)
	{
		if (token->heredoc > 0)
			close(token->heredoc);
		token->heredoc = open(formating(tmp, c->garbage),
				O_RDWR | O_CREAT | O_APPEND, 0644);
	}
}

bool	heredoc(t_tk *token, char *path, t_c *c)
{
	char	*tmp;
	pid_t	pid;

	tmp = ft_strjoin("/tmp/", ft_itoa(get_random(), c->garbage), c->garbage);
	hd_helper(tmp, token, 0, c);
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
				hd_helper(tmp, token, 2, c);
		}
		hd_helper(tmp, token, 1, c);
		return (unlink(tmp), true);
	}
}

void	exec_heredoc(t_tk *token, t_c *c)
{
	t_redic	*curr;

	curr = token->redics;
	token->is_last = 0;
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			if (g_signal == 169 || token->heredoc == -1)
				break ;
			if (token->heredoc > 0)
				close(token->heredoc);
			if (!heredoc(token, ft_strip('<', curr->content, c->garbage), c))
				return ;
			if (curr->next == NULL)
				token->is_last = 1;
		}
		curr = curr->next;
	}
}

void	check_iflast(t_tk *token)
{
	if (token->is_last || token->in == 0)
	{
		if (token->in > 0)
			close(token->in);
		token->in = token->heredoc;
	}
	else
	{
		if (token->heredoc > 0)
		{
			close(token->heredoc);
			token->heredoc = 0;
		}
	}
}
