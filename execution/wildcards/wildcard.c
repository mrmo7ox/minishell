/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:03:38 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/29 21:35:01 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*gen_dir(char **splited, int *i, int root, t_container *c)
{
	char	*dir;

	dir = NULL;
	if (!splited || !splited[*i])
		return (NULL);
	while (splited[*i] && !ft_chrstr('*', splited[*i]))
	{
		if (root == 0)
		{
			dir = ft_addchr(dir, '/', c);
			root = 69;
		}
		dir = ft_strjoin(dir, splited[*i], c->garbage);
		if (!dir)
			return (NULL);
		dir = ft_addchr(dir, '/', c);
		if (!dir)
			return (NULL);
		(*i)++;
	}
	return (dir);
}

void	expand_wildcards(char *arg, char *dir, t_wild **head, t_container *c)
{
	t_wu	utils;
	char	**splited;
	int		i;

	if (ft_chrstr('/', arg))
	{
		splited = ft_wild_split(arg, c, 0, 0);
		i = 0;
		dir = gen_dir(splited, &i, ft_chrindex(arg, '/'), c);
		if (!dir)
			return ;
	}
	else
	{
		splited = ft_wild_split(arg, c, 0, 0);
		i = 0;
		dir = ".";
	}
	utils.dir = dir;
	utils.split = splited;
	utils.i = &i;
	utils.head = head;
	utils.c = c;
	utils.entry = NULL;
	recursive_wild(&utils);
}

char	**convert_array(t_wild **head, t_container *c)
{
	char	**res;
	t_wild	*tmp;
	int		i;

	if (!head || !*head)
		return (NULL);
	res = ft_malloc((ft_wildsize(*head) + 1) * sizeof(char *), c->garbage);
	if (!res)
		return (NULL);
	tmp = *head;
	i = 0;
	while (tmp)
	{
		res[i] = tmp->arg;
		i++;
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}

char	**wildcards(char **args, t_container *c)
{
	t_wild	*head;
	int		i;

	head = NULL;
	i = 0;
	while (args[i])
	{
		if (ft_chrstr('*', args[i]))
		{
			expand_wildcards(args[i], ".", &head, c);
			i++;
			continue ;
		}
		ft_add_wild(&head, ft_new_wild(args[i], c));
		i++;
	}
	return (convert_array(&head, c));
}
