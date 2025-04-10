/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:12:30 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/10 11:53:46 by ihamani          ###   ########.fr       */
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

void	spc(char *line, int *i)
{
	while (ft_chrstr(line[*i], "<>|&(\"'") && line[*i] != '\0')
	{
		if (line[*i] == '(')
		{
			(*i)++;
			while (line[*i] != '\0' && line[*i] != ')')
				(*i)++;
		}
		else if (line[*i] == '\'')
		{
			(*i)++;
			while (line[*i] != '\0' && line[*i] != '\'')
				(*i)++;
		}
		else if (line[*i] == '"')
		{
			(*i)++;
			while (line[*i] != '\0' && line[*i] != '"')
				(*i)++;
		}
		(*i)++;
	}
}

void	strlen_spc(char *line, int *i)
{
	if (line[*i] == '(')
	{
		(*i)++;
		while (line[*i] != '\0' && line[*i] != ')')
			(*i)++;
		(*i)++;
	}
	else if (line[*i] == '\'')
	{
		(*i)++;
		(*i)++;
		while (line[*i] != '\0' && line[*i] != '\'')
			(*i)++;
		(*i)++;
	}
	else if (line[*i] == '"')
	{
		(*i)++;
		while (line[*i] != '\0' && line[*i] != '"')
			(*i)++;
		(*i)++;
	}
	else
		(*i)++;
}

void	add_string(int *num, char **res, char *line)
{
	int	i;
	int	j;
	int	word;

	i = num[0];
	j = num[1];
	word = num[2];
	if (i > j)
	{
		res[word] = malloc(sizeof(char) * ((i - j) + 1));
		if (!res[word])
		{
			free_the_split(res, word);
			exit(1);
		}
		(ft_copy (res[word], &line[j], (i - j)), word++);
	}
}
