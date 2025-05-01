/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:30:33 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/01 10:57:36 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_strinstr(char *haystack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	if (!haystack)
		return (false);
	while (haystack[i])
	{
		j = 0;
		while (needle[j] && haystack[i] && needle[j] == haystack[i])
		{
			j++;
			i++;
		}
		if (needle[j] == '\0')
			return (true);
		i++;
	}
	return (false);
}
