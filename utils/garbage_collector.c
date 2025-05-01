/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:34:17 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/01 10:33:23 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_garbage(t_gc **list)
{
	t_gc	*tmp;
	void	*next;

	if (!*list || !list)
		return ;
	tmp = *list;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->addr);
		free(tmp);
		tmp = next;
	}
	*list = NULL;
}
