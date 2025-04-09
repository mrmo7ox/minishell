/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:05:01 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/09 15:12:34 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 


// static void	ft_copy(char *dest, char *src, int len)
// {
// 	int	i;

// 	i = 0;
// 	while (src[i] && i < len)
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// }

static bool special_cases(char *str)
{
	if ((ft_strstr(str, "<<") || ft_strstr(str, ">>")) && *str != '\0')
		return (true);
	else if ((ft_strstr(str, "||") || ft_strstr(str, "&&")) && *str != '\0')
		return (true);
	if ((ft_strstr(str, "<") || ft_strstr(str, ">")) && *str != '\0')
		return (true);
	else if ((ft_strstr(str, "|") || ft_strstr(str, "&")) && *str != '\0')
		return (true);
	else if (*str != '\0' && ft_strstr(str , "<"))
		return (true);
	return (false);
}
static int	strlen_mod(char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && ft_chrstr(str[i], " "))
			i++;
		if (special_cases(str + i) && str[i] != '\0')
		{
			while(ft_chrstr(str[i], "<>|&") && str[i] != '\0')
				i++;
			words++;
			continue;
		}
		else if (str[i] != ' ' && str[i] != '\0')
			words++;
		while (!ft_chrstr(str[i], "<>|& ") && str[i] != '\0')
			i++;
	}
	printf("words number = %d\n", words);
	return (words);
}

// static char	**free_the_split(char **res, int words)
// {
// 	while (words)
// 	{
// 		free (res[words]);
// 		words--;
// 	}
// 	free(res);
// 	return (NULL);
// }

char	**ft_split(char *str, int i, int j)
{
	char	**res;
	int		words;
	
	words = strlen_mod(str);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	i = 0;
	words = 0;
	(void)i;
	(void)j;
	
	// while (str[i])
	// {
	// 	while (str[i] && str[i] == c)
	// 		i++;
	// 	j = i;
	// 	while (str[i] && str[i] != c)
	// 		i++;
	// 	if (i > j)
	// 	{
	// 		res[words] = malloc(sizeof(char) * ((i - j) + 1));
	// 		if (!res[words])
	// 			return (free_the_split(res, words));
	// 		(ft_copy (res[words], &str[j], (i - j)), words++);
	// 	}
	// }
	return (res[words] = NULL, res);
}
