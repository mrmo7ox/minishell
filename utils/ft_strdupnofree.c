/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupnofree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:01:26 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/03 11:06:14 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdupnofree(const char *source)
{
	char	*dup;
	int		len;

	if (!source)
		return (NULL);
	len = ft_strlen(source);
	dup = (char *)malloc((sizeof(char) * (len + 1)));
	if (dup == NULL)
		return (NULL);
	ft_memcpy(dup, source, len);
	dup[len] = '\0';
	return (dup);
}
