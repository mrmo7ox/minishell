/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:05:01 by moel-oua          #+#    #+#             */
/*   Updated: 2025/03/14 16:54:40 by moel-oua         ###   ########.fr       */
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
static int ft_strchr(char c, char *sap)
{
	int i;

	i = 0;
	while(sap[i] != '\0')
	{
		if(sap[i] == c)
			return (c);	
		i++;
	}
	return (0);
}
static int	in_sap(char *sap, char *str)
{
	int		i;
	int		words;
	char	old;

	words = 0;
	i = 0;
	while (str[i] != '\0' && str[i] != ' ')
	{
		if (!ft_strchr(str[i], sap))
			words++;
		while (!ft_strchr(str[i], sap) && (str[i] != '\0' && str[i] != ' '))
			i++;
		old = str[i];
		if (ft_strchr(str[i], sap))
		{
			words += 1;
			i++;
		}
		while (ft_strchr(str[i], sap) == old 
			&& (str[i] != '\0' && str[i] != ' '))
			i++;
	}
	return words;
}

static int	strlen_mod(char *str, char *sap)
{
	
	int	i;
	int	words;
	
	i = 0;
	words = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' && str[i] != '\0')
			i++;
		if (str[i] != ' ' && str[i] != '\0')
			words += in_sap(sap, &str[i]);
		while (str[i] != ' ' && str[i] != '\0')
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

bool	add_split_gc(t_gc **head ,char **res)
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

char	**ft_split(char *str, char *sap, int i, int j)
{
	char	**res;
	int		words;
	char	old;
	words = strlen_mod(str, sap);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' ))
			i++;
		j = i;
		if (str[i] && (str[i] != ' ' ) && ft_strchr(str[i], sap))
		{
			old = str[i];
			while (str[i] && (str[i] != ' ' ) && ft_strchr(str[i], sap) == old)
				i++;
		}
		else
		{
			while (str[i] && (str[i] != ' ' ) && !ft_strchr(str[i], sap))
				i++;
		}
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
