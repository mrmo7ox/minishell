/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 09:48:28 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/10 12:55:22 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_args_copy(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static int	strlen_mod(char *str)
{
	int		i;
	int		words;
	char	quote;
	bool	closed;

	closed = false;
	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		words++;
		while (str[i] && str[i] != ' ')
		{
			if (ft_chrstr(str[i], "\'\""))
			{
				quote = str[i];
				i++;
				while (str[i] && str[i] != quote)
					i++;
				if (str[i] == quote)
					i++;
				continue ;
			}
			i++;
		}
	}
	return (words);
}

static char	**free_the_split(char **res, int words)
{
	while (words--)
		free(res[words]);
	free(res);
	return (NULL);
}

char	**ft_args_split(char *str, t_gc **garbage, int i, int j)
{
	char	**res;
	int		words;
	int		word_count;
	char	quote;
	bool	closed;

	closed = false;
	words = 0;
	if (!str)
		return (NULL);
	word_count = strlen_mod(str);
	res = ft_malloc(sizeof(char *) * (word_count + 1), garbage);
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		j = i;
		while (str[i] && str[i] != ' ')
		{
			if (ft_chrstr(str[i], "\'\""))
			{
				quote = str[i];
				i++;
				while (str[i] && str[i] != quote)
					i++;
				if (str[i] == quote)
					i++;
				continue ;
			}
			i++;
		}
		if (i > j)
		{
			res[words] = ft_malloc(sizeof(char) * (i - j + 1), garbage);
			if (!res[words])
				return (free_the_split(res, words));
			ft_args_copy(res[words], &str[j], i - j);
			words++;
		}
	}
	res[words] = NULL;
	return (res);
}
