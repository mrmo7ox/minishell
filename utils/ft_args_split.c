/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 09:48:28 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/06 15:25:31 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_args_copy(char *dest, char *src, int len)
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

char	**ft_args_split(char *str, t_gc **garbage, int i, int j)
{
	char	**res;
	int		words;

	if (!str)
		return (NULL);
	words = strlen_mod(str, ' ');
	res = ft_malloc((sizeof(char *) * (words + 1)), garbage);
	if (!res)
		return (NULL);
	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		j = i;
		while (str[i] && str[i] != ' ')
			i++;
		if (i > j)
		{
			res[words] = ft_malloc((sizeof(char) * ((i - j) + 1)), garbage);
			if (!res[words])
				return (free_the_split(res, words));
			(ft_args_copy(remove_qoutes(res[words], garbage), &str[j], (i
						- j)), words++);
		}
	}
	return (res[words] = NULL, res);
}
