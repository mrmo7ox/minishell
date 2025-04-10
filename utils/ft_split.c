/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:05:01 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/10 11:53:30 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

static bool	special_cases(char *str)
{
	if ((ft_strstr(str, "<<") || ft_strstr(str, ">>")) && *str != '\0')
		return (true);
	else if ((ft_strstr(str, "'") || ft_strstr(str, "\"")) && *str != '\0')
		return (true);
	else if ((ft_strstr(str, "(") || ft_strstr(str, ")")) && *str != '\0')
		return (true);
	else if ((ft_strstr(str, "||") || ft_strstr(str, "&&")) && *str != '\0')
		return (true);
	else if ((ft_strstr(str, "<") || ft_strstr(str, ">")) && *str != '\0')
		return (true);
	else if ((ft_strstr(str, "|") || ft_strstr(str, "&")) && *str != '\0')
		return (true);
	else if (*str != '\0' && ft_strstr(str, "<"))
		return (true);
	return (false);
}

static int	strlen_mod(char *line)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && ft_chrstr(line[i], " "))
			i++;
		if (special_cases(line + i) && line[i] != '\0')
		{
			while (ft_chrstr(line[i], "<>|&(\"'") && line[i] != '\0')
				strlen_spc(line, &i);
			words++;
			continue ;
		}
		else if (line[i] != ' ' && line[i] != '\0')
			words++;
		while (!ft_chrstr(line[i], "<>|&) ") && line[i] != '\0')
			i++;
	}
	return (words);
}

static void	bs(int *num, char **res, char *line)
{
	spc(line, &num[0]);
	add_string(num, res, line);
	num[2]++;
}
<<<<<<< HEAD

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
=======
//0 i,1 j, 2 words

char	**ft_split(char *line)
>>>>>>> 9569a960daad3d1636abc6edea6ef8f09c53e9a9
{
	char	**res;
	int		num[3];

	num[2] = strlen_mod(line);
	res = malloc(sizeof(char *) * (num[2] + 1));
	if (!res)
		return (NULL);
	num[0] = 0;
	num[2] = 0;
	while (line[num[0]])
	{
		while (line[num[0]] != '\0' && ft_chrstr(line[num[0]], " "))
			num[0]++;
		num[1] = num[0];
		if (special_cases(line + num[0]) && line[num[0]] != '\0')
		{
			bs(num, res, line);
			continue ;
		}
		while (!ft_chrstr(line[num[0]], "<>|&('\") ") && line[num[0]] != '\0')
			num[0]++;
		add_string(num, res, line);
		num[2]++;
	}
	return (res[num[2]] = NULL, res);
}
