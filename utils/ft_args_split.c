/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 09:48:28 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/02 10:56:12 by moel-oua         ###   ########.fr       */
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
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (ft_whitespaces(str[i]))
			i++;
		if (!str[i])
			break ;
		words++;
		while (str[i] && !ft_whitespaces(str[i]))
		{
			if (ft_chrstr(str[i], "\'\""))
			{
				skip_it(str, &i);
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

bool	more_things(t_as *u)
{
	while (u->str[u->i] && !ft_whitespaces(u->str[u->i]))
	{
		if (ft_chrstr(u->str[u->i], "\'\""))
		{
			skip_it(u->str, &u->i);
			continue ;
		}
		(u->i)++;
	}
	if (u->i > u->j)
	{
		u->res[u->words] = ft_malloc(sizeof(char *) * (u->i - u->j + 1),
				u->garbage);
		if (!u->res[u->words])
		{
			free_the_split(u->res, u->words);
			return (false);
		}
		ft_args_copy(u->res[u->words], &u->str[u->j], u->i - u->j);
		(u->words)++;
	}
	return (true);
}

char	**ft_args_split(char *str, t_gc **garbage)
{
	t_as	*u;

	if (!str)
		return (gen_arry(ft_strdup("", garbage), garbage));
	u = ft_malloc(sizeof(t_as), garbage);
	u->words = 0;
	u->str = str;
	u->garbage = garbage;
	u->words_counter = strlen_mod(str);
	u->res = ft_malloc(sizeof(char *) * (u->words_counter + 1), garbage);
	if (!u->res)
		return (NULL);
	u->i = 0;
	while (str[u->i])
	{
		while (str[u->i] && ft_whitespaces(str[u->i]))
			(u->i)++;
		if (!str[u->i])
			break ;
		u->j = u->i;
		if (!more_things(u))
			return (NULL);
	}
	u->res[u->words] = NULL;
	return (u->res);
}
