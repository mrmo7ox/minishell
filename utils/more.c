/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:25:50 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/31 15:23:56 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_qoutes	*ft_new_node(int open, int close, t_qtype type, t_gc **garbage)
{
	t_qoutes	*node;

	node = ft_malloc(sizeof(t_qoutes), garbage);
	if (!node)
		return (NULL);
	node->open_index = open;
	node->close_index = close;
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_add_arg(t_arg **head, t_arg *new)
{
	t_arg	*last;

	if (!(head) || !new)
		return ;
	if (!(*head))
	{
		(*head) = new;
		new->prev = NULL;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

void	skip_it(char *str, int *i)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		(*i)++;
}
