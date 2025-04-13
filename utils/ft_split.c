/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:05:01 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/13 15:05:44 by moel-oua         ###   ########.fr       */
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

static bool	special_cases(char *str)
{
	if ((ft_strstr(str, "<<") || ft_strstr(str, ">>")) && *str != '\0')
		return (true);
	else if ((ft_strstr(str, "(") || ft_strstr(str, ")")) && *str != '\0')
		return (true);
	else if ((ft_strstr(str, "||") || ft_strstr(str, "&&")) && *str != '\0')
		return (true);
	else if ((ft_strstr(str, "<") || ft_strstr(str, ">")) && *str != '\0')
		return (true);
	else if ((ft_strstr(str, "|") || ft_strstr(str, "&")) && *str != '\0')
		return (true);
	else if (*str != '\0' && ft_strstr(str , "<"))
		return (true);
	return (false);
}

static int	strlen_mod(char *line)
{
	int	i;
	int	words;
	int count;
	i = 0;
	words = 0;
	count = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && ft_chrstr(line[i], " "))
			i++;
		if (special_cases(line + i) && line[i] != '\0')
		{
			if(ft_chrstr(line[i], "<>|&(") && line[i] != '\0')
				{
					if(line[i] == '(')
					{
						i++;
						count++;
						while(line[i] != '\0' && count > 0)
						{
							if(line[i] == ')' && count > 0)
								count--;
							else if(line[i] == '(' && count > 0)
								count++;
							i++;
						}
					}
					else if(line[i] == '|')
					{
						i++;
						while(line[i] != '\0' && line[i] == '|')
							i++;
												
					}
					else if(line[i] == '&')
					{
						i++;
						while(line[i] != '\0' && line[i] == '&')
							i++;
												
					}
					else
						i++;
				}
			words++;
			continue ;
		}
		else if (line[i] != ' ' && line[i] != '\0')
			words++;
		while (!ft_chrstr(line[i], "<>|&)") && line[i] != '\0')
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
void	add_string(int i, int j, char **res, int words, char *line)
{
	if (i > j)
	{
		res[words] = malloc(sizeof(char) * ((i - j) + 1));
		if (!res[words])
		{
			free_the_split(res, words);
			exit(1);
		}
		(ft_copy (res[words], &line[j], (i - j)), words++);
	}
}
char	**ft_split(char *line, int i, int j)
{
	char	**res;
	int		words;
	
	words = strlen_mod(line);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	i = 0;
	words = 0;
	int count = 0;
	while (line[i])
	{
		j = i;
		while (line[i] != '\0' && ft_chrstr(line[i], " "))
			i++;
		if (special_cases(line + i) && line[i] != '\0')
		{
			if(ft_chrstr(line[i], "<>|&(") && line[i] != '\0')
				{
					if(line[i] == '(')
					{
						i++;
						count++;
						while(line[i] != '\0' && count > 0)
						{
							printf("[%c]\n", line[i]);
							if(line[i] == ')' && count > 0)
								count--;
							else if(line[i] == '(' && count > 0)
								count++;
							i++;
						}
					}
					else if(line[i] == '|')
					{
						i++;
						while(line[i] != '\0' && line[i] == '|')
							i++;
					}
					else if(line[i] == '&')
					{
						i++;
						while(line[i] != '\0' && line[i] == '&')
							i++;
					}
					else if(line[i] == '<')
					{
						i++;
						while(line[i] != '\0' && line[i] == '<')
							i++;
					}
					else if(line[i] == '>')
					{
						i++;
						while(line[i] != '\0' && line[i] == '>')
							i++;
					}
					else
						i++;
				}
			add_string(i, j , res, words, line);
			words++;
			continue ;
		}
		while (!ft_chrstr(line[i], "<>|&()") && line[i] != '\0')
			i++;
		add_string(i, j , res, words, line);
		words++;
	}
	return (res[words] = NULL, res);
}
