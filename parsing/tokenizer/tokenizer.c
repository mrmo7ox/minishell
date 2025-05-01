/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:05:51 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/01 11:15:34 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	adding_redirects(t_tk **head, t_gc **garbage)
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
			ft_minisplit(&new, garbage, current, m_utils);
			current->redics = new;
		}
		current = current->next;
	}
}

bool	tokenizer(t_gc **garbage, char *line)
{
	t_tk	*splitted;
	t_leaf	*root;

	splitted = NULL;
	root = NULL;
	ft_split(&splitted, garbage, line);
	if (ft_lstsize(splitted) == 0)
		return (false);
	adding_redirects(&splitted, garbage);
	root = build_ast(splitted, garbage);
	if (!root)
		return (false);
	linker(&root);
	return (true);
}
