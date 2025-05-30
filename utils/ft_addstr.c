/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:26:30 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/29 21:39:20 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_addstr(char *str, char *str2, t_c *c)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	len1 = 0;
	len2 = 0;
	if (!str)
		return (str2);
	if (str)
		while (str[len1])
			len1++;
	if (str2)
		while (str2[len2])
			len2++;
	new_str = ft_malloc(len1 + len2 + 1, c->garbage);
	if (!new_str)
		return (NULL);
	if (str)
		ft_strcpy(new_str, str);
	if (str2)
		ft_strcpy(new_str + len1, str2);
	new_str[len1 + len2] = '\0';
	return (new_str);
}
