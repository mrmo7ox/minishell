/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:45:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/02 13:23:12 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_dollar	is_dollar_in_quotes(t_qoutes **quotes, int index)
{
	t_qoutes	*curr;

	if (!quotes || !*quotes)
		return (OUTSIDE);
	curr = *quotes;
	while (curr)
	{
		if (curr->type == DQOUTE && index > curr->open_index
			&& index < curr->close_index)
			return (INSIDED);
		else if (curr->type == SQOUTE && index > curr->open_index
			&& index < curr->close_index)
			return (INSIDES);
		curr = curr->next;
	}
	return (OUTSIDE);
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
	t_expand	*curr;

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
