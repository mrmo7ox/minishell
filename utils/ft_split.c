/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:05:01 by moel-oua          #+#    #+#             */
/*   Updated: 2025/03/14 15:09:59 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

static void	ft_copy(char *dest, char *src, int len)
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
		free (res[words]);
		words--;
	}
	free(res);
	return (NULL);
}

bool	*add_split_gc(t_gc **head ,char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		ft_add_gc (head, ft_new_gc_node(res[i]));
		i++;
	}
	ft_add_gc (head, ft_new_gc_node(res));
	return (NULL);
}

char	**ft_split(char *str, char c, char c2, int i, int j)
{
	char	**res;
	int		words;

	words = strlen_mod(str, c);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == c || str[i] == c2))
			i++;
		j = i;
		while (str[i] && (str[i] != c || str[i] != c2))
			i++;
		if (i > j)
		{
			res[words] = malloc(sizeof(char) * ((i - j) + 1));
			if (!res[words])
				return (free_the_split(res, words));
			(ft_copy (res[words], &str[j], (i - j)), words++);
		}
	}
	return (res[words] = NULL, res);
}