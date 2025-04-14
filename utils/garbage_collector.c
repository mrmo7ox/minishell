/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:34:17 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/14 13:02:32 by ihamani          ###   ########.fr       */
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
