/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:05:01 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/16 12:57:47 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

static char	*ft_copy( char *src, int len)
{
	int	i;
	char	*dup;

	i = 0;
	if (!src || len == 0)
		return (ft_strdup(""));
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (src[i] && i < len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

bool	special_cases(char *str)
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


void	ft_split(t_tk **res, t_gc **garbage, char *line, int i, int j)
{
	int		words;
	*res = NULL;
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
			if(ft_chrstr(line[i], "<>|&()") && line[i] != '\0')
				{
					if(line[i] == '(')
					{
						i++;
						int x = i;
						while(line[x] != ')' && line[x] != '\0')
						{
							if (ft_chrstr(line[x], "|&><"))
							{
								count++;
								break;
							}
							x++;				
						}
						continue;

					}
					else if(line[i] == ')')
					{
						i++;
						count--;
						continue;
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
			ft_add_tk(res, ft_new_tk_node(ft_copy (&line[j], (i - j)), count, garbage, words));
			words++;
			continue ;
		}
		while (!ft_chrstr(line[i], "<>|&()") && line[i] != '\0')
			i++;
		ft_add_tk(res, ft_new_tk_node(ft_copy (&line[j], (i - j)), count, garbage, words));
		words++;
	}
}
