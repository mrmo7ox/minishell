/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:33:52 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/27 11:27:35 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2, t_gc **garbage)
{
	int		len_s1;
	int		len_s2;
	char	*new;

	if (!s1)
		return (ft_strdup(s2, garbage));
	if (!s2)
		return (ft_strdup(s1, garbage));
	if (!s2 && !s1)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new = (char *)ft_malloc(sizeof(char) * (1 + len_s1 + len_s2), garbage);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, s1, len_s1);
	ft_memcpy(new + len_s1, s2, len_s2);
	new[len_s1 + len_s2] = '\0';
	return (new);
}
