/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:07:37 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/31 09:47:03 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_addchr(char *str, char chr, t_c *c)
{
	size_t	len;
	char	*new_str;

	len = 0;
	if (str)
		while (str[len])
			len++;
	new_str = ft_malloc(len + 2, c->garbage);
	if (!new_str)
		return (NULL);
	if (str)
		ft_strcpy(new_str, str);
	new_str[len] = chr;
	new_str[len + 1] = '\0';
	return (new_str);
}
