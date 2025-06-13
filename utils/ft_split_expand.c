/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:41:41 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/02 10:46:58 by moel-oua         ###   ########.fr       */
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
				return (NULL);
			(ft_expand_copy(res[words], &str[j], (i - j)), words++);
		}
	}
	return (res[words] = NULL, res);
}
