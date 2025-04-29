/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:34:17 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/28 20:48:11 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_garbage(t_gc **list)
{
	t_gc	*tmp;

	if (!*list || !list)
		return ;
	tmp = *list;
	while (tmp)
	{
		free(tmp->addr);
		tmp = tmp->next;
	}
	free(list);
}
