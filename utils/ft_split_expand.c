/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:41:41 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/31 14:44:20 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_expand_copy(char *dest, char *src, int len)
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

static int	strlen_mod(char *str)
{
	int	i;
	int	words;
	int	j;

	j = 0;
	i = 0;
	words = 0;
	while (str[i])
	{
		j = i;
		if (str[i] == '$')
			skip_hit(&i, str);
		else
			not_hit(&i, str);
		if (i > j)
		{
			words++;
		}
	}
	return (words);
}

static char	**free_the_split(char **res, int words)
{
	while (words)
	{
		free(res[words]);
		words--;
	}
	free(res);
	return (NULL);
}

char	**ft_expand_split(char *str, t_c *c, int i, int j)
{
	char	**res;
	int		words;

	words = strlen_mod(str);
	res = ft_malloc(sizeof(char *) * (words + 1), c->garbage);
	if (!res)
		return (NULL);
	i = 0;
	words = 0;
	while (str[i])
	{
		j = i;
		if (str[i] == '$')
			skip_hit(&i, str);
		else
			not_hit(&i, str);
		if (i > j)
		{
			res[words] = ft_malloc(sizeof(char) * ((i - j) + 1), c->garbage);
			if (!res[words])
				return (free_the_split(res, words));
			(ft_expand_copy(res[words], &str[j], (i - j)), words++);
		}
	}
	return (res[words] = NULL, res);
}
