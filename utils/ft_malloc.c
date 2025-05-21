/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:51:55 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/21 10:01:09 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_malloc(size_t size, t_gc **garbage)
{
	void	*addr;

	addr = malloc(size);
	if (!addr)
	{
		perror("malloc");
		free_garbage(garbage);
		exit(1);
	}
	ft_add_gc(garbage, ft_new_gc_node(addr));
	return (addr);
}
