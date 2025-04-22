/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:36:13 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/22 15:44:12 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *pwd()
{
	char *buff;

	buff = getcwd(NULL, 0);
	if (!buff)
		return (NULL);
	// ft_add_gc(gg, ft_new_gc_node(buff));
	// printf("%s\n", buff);
	return (buff);
}
static void	ft_fill(char const *s1, char const *s2, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (strdup(s2));
	else if (s2 == NULL)
		return (strdup(s1));
	len1 = strlen(s1);
	len2 = strlen(s2);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_fill(s1, s2, str);
	return (str);
}

int main(int ac, char **av)
{
	char *buff;

	buff = pwd();
	printf("%s\n", buff);
	buff = ft_strjoin(buff, "/");
	buff = ft_strjoin(buff, av[1]);
	printf("%s\n", buff);
	if (chdir(buff) == -1)
		printf("no such directory\n");
}