/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:14:42 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/08 12:30:28 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expander(t_tk *token, t_gc **garbage, t_env **ft_env)
{
	t_list		tmp;
	t_qoutes	*curr;
	t_expand	*currs;

	if (!token && !(token->token))
		return ;
	tmp = split_expand(token->token, garbage, ft_env);
	curr = *(tmp.qoutes);
	while (curr)
	{
		if (curr->type == SQOUTE)
			printf("[%d][%d][single]\n", curr->open_index, curr->close_index);
		else
			printf("[%d][%d][double]\n", curr->open_index, curr->close_index);
		curr = curr->next;
	}
	printf("======[TEST]======\n");
	currs = *(tmp.expand);
	while (currs)
	{
		printf("[%d][%d]\n", currs->start, currs->end);
		currs = currs->next;
	}
}
