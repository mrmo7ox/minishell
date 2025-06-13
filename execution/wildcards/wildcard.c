/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:03:38 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/02 10:38:37 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	hardcode_case(char **splited, int *i, char **dir, t_c *c)
{
	if (!ft_strcmp("/", splited[*i]))
	{
		*dir = ft_strjoin(*dir, splited[*i], c->garbage);
		(*i)++;
		return (true);
	}
	return (false);
}

char	*gen_dir(char **splited, int *i, int root, t_c *c)
{
	char	*dir;

	dir = NULL;
	if (!splited || !splited[*i])
		return (NULL);
	while (splited[*i] && !ft_chrstr('*', splited[*i]))
	{
		if (hardcode_case(splited, i, &dir, c))
			continue ;
		if (root == 0 && !dir)
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

void	expand_wildcards(char *arg, char *dir, t_wild **head, t_c *c)
{
	t_wu	utils;
	char	**splited;
	int		i;

	if ((ft_strlen(arg) > 0 && arg[0] == '/') || ft_strinstr(arg, "//"))
		return ;
	if (ft_strlen(arg) >= 2 && arg[0] == '.' && arg[1] == '/')
		arg = ft_substr(arg, 2, ft_strlen(arg) - 1, c->garbage);
	splited = ft_wild_split(arg, c, 0, 0);
	if (!splited)
		return ;
	i = 0;
	dir = "./";
	utils.dir = dir;
	utils.split = splited;
	utils.i = &i;
	utils.head = head;
	utils.c = c;
	utils.entry = NULL;
	recursive_wild(&utils);
}

char	**convert_array(t_wild **head, t_c *c)
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
		if (ft_strlen(tmp->arg) >= 2 && tmp->arg[0] == '.' && tmp->arg[1] == '/'
			&& tmp->flag)
			tmp->arg = ft_substr(tmp->arg, 2, ft_strlen(tmp->arg), c->garbage);
		if (tmp->arg[ft_strlen(tmp->arg) - 1] == '/' && tmp->flag)
			tmp->arg = ft_substr(tmp->arg, 0, ft_strlen(tmp->arg) - 1,
					c->garbage);
		res[i] = tmp->arg;
		i++;
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}

char	**wildcards(char **args, t_c *c)
{
	t_wild	*head;
	int		i;
	int		size;

	head = NULL;
	i = 0;
	while (args[i])
	{
		if (ft_chrstr('*', args[i]) && !has_qoute(args[i]))
		{
			size = ft_wildsize(head);
			expand_wildcards(args[i], ".", &head, c);
			if (size == ft_wildsize(head))
				ft_add_wild(&head, ft_new_wild(args[i], false, c));
			i++;
			continue ;
		}
		ft_add_wild(&head, ft_new_wild(args[i], false, c));
		i++;
	}
	return (convert_array(&head, c));
}
