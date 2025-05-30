/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:12:51 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/05 20:49:04 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_copy(char *src, int len, t_gc **garbage)
{
	char	*dup;
	int		i;

	i = 0;
	dup = ft_malloc(len + 1, garbage);
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

t_type	special_cases(char *str)
{
	if (str && ft_strstr(str, "||"))
		return (OR);
	else if (str && ft_strstr(str, "&&"))
		return (AND);
	else if (str && ft_strstr(str, "|"))
		return (PIPE);
	return (COMMAND);
}
