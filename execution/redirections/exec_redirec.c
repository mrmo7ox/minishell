/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 09:44:05 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/05 20:41:46 by moel-oua         ###   ########.fr       */
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
		dup2(0, redics->fd);
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
		dup2(1, redics->fd);
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
		dup2(1, redics->fd);
		return (true);
	}
}

bool	heredoc(t_redic *redics, char *path, t_gc **garbage)
{
	char	*tmp;
	char	*line;

	line = NULL;
	tmp = ft_strjoin("/tmp/", ft_itoa(get_random(), garbage), garbage);
	redics->fd = open(formating(tmp, garbage), O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (redics->fd == -1)
		return (false);
	else
	{
		dup2(0, redics->fd);
		while (ft_strcmp(formating(path, garbage), line))
		{
			line = readline("heredoc>");
			write(redics->fd, line, ft_strlen(line));
		}
		return (true);
	}
}

bool	exec_redirec(t_tk *token, t_gc **garbage)
{
	t_redic	*curr;
	char	**parts;

	(void)garbage;
	(void)parts;
	curr = token->redics;
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
			if (!heredoc(curr, ft_strip('<', curr->content, garbage), garbage))
				return (false);
		}
		curr = curr->next;
	}
	return (true);
}

static void	handle_command_node(t_leaf *node, t_gc **garbage)
{
	if (!node || node->type != COMMAND)
		return ;
	if (node->token && node->token->redics)
	{
		if (!exec_redirec(node->token, garbage))
		{
			return ;
		}
	}
}

static void	traverse_child(t_leaf *child, t_gc **garbage)
{
	if (!child)
		return ;
	if (child->type == COMMAND)
		handle_command_node(child, garbage);
	else
		init_redirection(&child, garbage);
}

void	init_redirection(t_leaf **root, t_gc **garbage)
{
	t_leaf *tmp;

	if (!root || !(*root))
		return ;
	tmp = *root;
	if (tmp->type == COMMAND)
		handle_command_node(tmp, garbage);

	if (tmp->right)
		traverse_child(tmp->right, garbage);
	if (tmp->left)
		traverse_child(tmp->left, garbage);
}