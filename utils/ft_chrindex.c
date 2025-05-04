/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:47:47 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/04 09:52:05 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_chrindex(char *line, char chr)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == chr)
			return (i);
		i++;
	}
	return (-1);
}
