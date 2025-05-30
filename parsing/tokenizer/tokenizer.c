/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:05:51 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/30 18:00:34 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	adding_redirects(t_tk **head, t_c *c)
{
	t_tk	*current;
	t_redic	*new;
	t_mini	m_utils;

	if (!head)
		return ;
	current = (*head);
	while (current)
	{
		current->redics = NULL;
		if (current->type == COMMAND)
		{
			new = NULL;
			m_utils.i = 0;
			m_utils.line = current->token;
			ft_minisplit(&new, c, current, m_utils);
			current->redics = new;
		}
		current = current->next;
	}
}

bool	tokenizer(t_leaf **root, t_c *c, char *line)
{
	t_tk	*splitted;

	splitted = NULL;
	ft_split(&splitted, c->garbage, line);
	if (ft_lstsize(splitted) == 0)
		return (false);
	adding_redirects(&splitted, c);
	(*root) = build_ast(splitted, c->garbage);
	if (!(*root))
		return (false);
	return (true);
}
