/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:31:21 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/04 09:52:24 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	buffer_size(char chr, char *line)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != chr)
		{
			len++;
		}
		i++;
	}
	return (len);
}

char	*ft_strip(char chr, char *line, t_gc **garbage)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!line)
		return (NULL);
	new = ft_malloc((buffer_size(chr, line) + 1), garbage);
	if (!new)
		return (NULL);
	while (line[i])
	{
		if (line[i] != chr)
		{
			new[j] = line[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}
