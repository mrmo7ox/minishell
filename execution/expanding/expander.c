/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:14:42 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/03 10:10:13 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expander(t_tk *token, t_gc **garbage)
{
	t_expander res;

	if (token && token->token)
	{
		res = split_expand(token->token, garbage);
		t_part *curr;

		curr = res.result;
		while (curr)
		{
			// if (curr->expandable)
			printf("[%s][%d]\n", curr->content, curr->expandable);
			curr = curr->next;
		}
	}
}