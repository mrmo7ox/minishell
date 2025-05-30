/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 09:44:05 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/30 11:21:02 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**gen_arry(char *line, t_c *c)
{
	char	**new;

	new = ft_malloc(sizeof(char *) * 2, c->garbage);
	new[0] = formating(line, c->garbage);
	new[1] = NULL;
	return (new);
}

bool	in_files(t_tk *token, char *path, t_c *c)
{
	char	**tmp;

	if (!check_redr_file(remove_qoutes(path, c)))
	{
		token->in = -1;
		errno = 2;
		return (perror(path), false);
	}
	tmp = expander(gen_arry(path, c), c);
	if ((!tmp || !tmp[0] || (tmp[0] && tmp[1])))
	{
		token->in = -1;
		return (ft_putstr_fd(path, 2), ft_putstr_fd(": ambiguous redirect\n",
				2), set_status(1, -1), false);
	}
	if (token->in)
		close(token->in);
	token->in = open(tmp[0], O_RDONLY);
	if (token->in == -1)
	{
		perror(tmp[0]);
		return (set_status(1, -1), false);
	}
	else
		return (true);
}

bool	out_files(t_tk *token, char *path, t_c *c)
{
	char	**tmp;

	if (!check_redr_file(remove_qoutes(path, c)))
	{
		token->out = -1;
		errno = 2;
		return (perror(path), false);
	}
	tmp = expander(gen_arry(path, c), c);
	if (!tmp || !tmp[0] || (tmp[0] && tmp[1]))
	{
		set_status(1, -1);
		token->out = -1;
		return (ft_putstr_fd(path, 2), ft_putstr_fd(": ambiguous redirect\n",
				2), false);
	}
	if (token->out > 0)
		close(token->out);
	token->out = open(tmp[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (token->out == -1)
		return (set_status(1, -1), perror(tmp[0]), false);
	else
		return (true);
}

bool	append_files(t_tk *token, char *path, t_c *c)
{
	char	**tmp;

	if (!check_redr_file(remove_qoutes(path, c)))
	{
		token->out = -1;
		errno = 2;
		return (perror(path), false);
	}
	tmp = expander(gen_arry(path, c), c);
	if (!tmp || !tmp[0] || (tmp[0] && tmp[1]))
	{
		token->out = -1;
		return (ft_putstr_fd(path, 2), ft_putstr_fd(": ambiguous redirect\n",
				2), set_status(1, -1), false);
	}
	if (token->out > 0)
		close(token->out);
	token->out = open(tmp[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (token->out == -1)
	{
		perror(tmp[0]);
		return (set_status(1, -1), false);
	}
	else
		return (true);
}

bool	exec_redirec(t_tk *token, t_c *c)
{
	t_redic	*curr;

	curr = token->redics;
	token->in = 0;
	token->out = 0;
	while (curr)
	{
		if (!ext_exe_redr(&curr, c, token))
		{
			if (token->heredoc > 0)
				close(token->heredoc);
			set_status(1, -1);
			return (false);
		}
		curr = curr->next;
	}
	check_iflast(token);
	return (true);
}
