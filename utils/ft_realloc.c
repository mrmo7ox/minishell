/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:21:33 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/29 10:44:39 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_realloc(char **buffer, int plus, t_gc **garbage)
{
	char	**new;
	int		old_size;
	int		i;
	int		new_size;

	old_size = 0;
	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[old_size])
		old_size++;
	new_size = old_size + plus;
	new = ft_malloc(sizeof(char *) * (new_size + 1), garbage);
	if (!new)
		return (NULL);
	while (i < old_size)
	{
		new[i] = ft_strdup(buffer[i]);
		i++;
	}
	new[i] = NULL;
	free(buffer);
	return (new);
}
