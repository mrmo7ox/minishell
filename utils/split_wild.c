/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wild.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:41:41 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/29 21:39:20 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_wild_copy(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	while (src[i] && i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static int	strlen_mod(char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] != c && str[i] != '\0')
			words++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (words);
}

char	**ft_wild_split(char *str, t_c *c, int i, int j)
{
	char	**res;
	int		words;

	words = strlen_mod(str, '/');
	res = ft_malloc(sizeof(char *) * (words + 1), c->garbage);
	if (!res)
		return (NULL);
	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && str[i] == '/')
			i++;
		j = i;
		while (str[i] && str[i] != '/')
			i++;
		if (i > j)
		{
			res[words] = ft_malloc(sizeof(char) * ((i - j) + 1), c->garbage);
			if (!res[words])
				return (NULL);
			(ft_wild_copy(res[words], &str[j], (i - j)), words++);
		}
	}
	return (res[words] = NULL, res);
}
