/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:21:33 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/04 10:28:50 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_realloc(char **buffer, int plus, t_gc **gc)
{
	char	**new;
	int		old_size;
	int		i;
	int		new_size;

	old_size = 0;
	i = 0;
	if (!buffer)
		return (ft_malloc(plus + 1 * sizeof(char *), gc));
	while (buffer[old_size])
		old_size++;
	new_size = old_size + plus;
	new = ft_malloc(sizeof(char *) * (new_size), gc);
	if (!new)
		return (NULL);
	while (i < old_size)
	{
		new[i] = ft_strdup(buffer[i], gc);
		i++;
	}
	new[i] = NULL;
	free(buffer);
	return (new);
}
