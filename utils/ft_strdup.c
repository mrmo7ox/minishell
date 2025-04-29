/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:42:34 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/29 09:43:12 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *source, t_gc **gg)
{
	char	*dup;
	int		len;

	if (!source)
		return (NULL);
	len = ft_strlen(source);
	dup = (char *)ft_malloc((sizeof(char) * (len + 1)), gg);
	if (dup == NULL)
		return (NULL);
	ft_memcpy (dup, source, len);
	dup[len] = '\0';
	return (dup);
}
