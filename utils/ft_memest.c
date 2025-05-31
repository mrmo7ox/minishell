/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:41:21 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/31 09:46:21 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*new_s;
	size_t	i;

	if (!s || !c)
		return (NULL);
	i = 0;
	new_s = (char *)s;
	while (i < n)
	{
		*new_s = c;
		i++;
		new_s++;
	}
	return (s);
}
