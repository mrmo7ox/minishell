/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:34:17 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/05 13:04:48 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_garbage(t_gc **list)
{
	t_gc	*tmp;
	void	*next;

	printf("in the garbage!\n");
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
