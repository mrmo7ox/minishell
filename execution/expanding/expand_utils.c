/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:45:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/09 10:44:27 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_dollar_in_quotes(t_qoutes **quotes, int index)
{
	t_qoutes	*curr;

	if (!quotes || !*quotes)
		return (true);
	curr = *quotes;
	(void)index;
	while (curr)
	{
		if (curr->type == DQOUTE && index > curr->open_index
			&& index < curr->close_index)
			return (true);
		else if (curr->type == SQOUTE && index > curr->open_index
			&& index < curr->close_index)
			return (false);
		curr = curr->next;
	}
	return (true);
}

t_qoutes	*is_im_quotes(t_qoutes **quotes, int index)
{
	t_qoutes	*curr;

	if (!quotes || !*quotes)
		return (NULL);
	curr = *quotes;
	while (curr)
	{
		if (index == curr->open_index || index == curr->close_index)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

t_expand	*is_index_on_dollar(t_expand **dollars, int index)
{
	t_expand *curr;

	if (!dollars || !*dollars)
		return (NULL);
	curr = *dollars;
	while (curr)
	{
		if (index == curr->start)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}