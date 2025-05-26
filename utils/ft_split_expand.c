/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:41:41 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/26 17:23:44 by moel-oua         ###   ########.fr       */
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
	int		i;
	int		words;
	int		j;
	char	qoute;

	j = 0;
	i = 0;
	words = 0;
	while (str[i])
	{
		j = i;
		if (str[i] == '$')
		{
			i++;
			if (ft_isdigit(str[i]) || ft_chrstr(str[i], "~$#@!^&*?"))
			{
				i++;
			}
			else if (ft_isalnum(str[i]) || str[i] == '_')
			{
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
			}
		}
		else
		{
			while (str[i] && !ft_chrstr(str[i], "$"))
			{
				if (ft_chrstr(str[i], "\"'"))
				{
					qoute = str[i];
					i++;
					while (str[i] && str[i] != qoute)
					{
						i++;
					}
					if (qoute == str[i])
						i++;
					continue ;
				}
				i++;
			}
		}
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

char	**ft_expand_split(char *str, t_container *c, int i, int j)
{
	char **res;
	int words;
	char qoute;
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
		{
			i++;
			if (ft_isdigit(str[i]) || ft_chrstr(str[i], "$#@!^&*?"))
			{
				i++;
			}
			else if (ft_isalnum(str[i]) || str[i] == '_')
			{
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				{
					i++;
				}
			}
		}
		else
		{
			while (str[i] && !ft_chrstr(str[i], "$"))
			{
				if (ft_chrstr(str[i], "\"'"))
				{
					qoute = str[i];
					i++;
					while (str[i] && str[i] != qoute)
					{
						i++;
					}
					if (qoute == str[i])
						i++;
					continue ;
				}
				i++;
			}
		}
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