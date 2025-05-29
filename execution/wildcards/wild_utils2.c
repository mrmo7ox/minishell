/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:58:49 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/29 21:23:04 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	current_dir(char *line)
{
	return (!ft_strcmp(".", line) || !ft_strcmp("..", line));
}

int	is_dir(char *line)
{
	DIR	*dir;

	dir = opendir(line);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

static void	handle_wildcard_match(t_wu *wu)
{
	char	*path;
	int		j;
	t_wu	new_wu;

	if (!ismatch(wu->entry->d_name, wu->split[*wu->i]))
		return ;
	path = ft_strjoin(wu->dir, wu->entry->d_name, wu->c->garbage);
	path = ft_addchr(path, '/', wu->c);
	if (is_dir(path))
	{
		j = *wu->i + 1;
		new_wu.dir = path;
		new_wu.split = wu->split;
		new_wu.i = &j;
		new_wu.head = wu->head;
		new_wu.c = wu->c;
		new_wu.entry = NULL;
		recursive_wild(&new_wu);
	}
	else if (!wu->split[*wu->i + 1])
		ft_add_wild(wu->head, ft_new_wild(path, wu->c));
}

static void	handle_exact_match(t_wu *wu)
{
	char	*path;
	int		j;
	t_wu	new_wu;

	if (ft_strcmp(wu->entry->d_name, wu->split[*wu->i]) != 0)
		return ;
	path = ft_strjoin(wu->dir, wu->entry->d_name, wu->c->garbage);
	path = ft_addchr(path, '/', wu->c);
	if (is_dir(path))
	{
		j = *wu->i + 1;
		new_wu.dir = path;
		new_wu.split = wu->split;
		new_wu.i = &j;
		new_wu.head = wu->head;
		new_wu.c = wu->c;
		new_wu.entry = NULL;
		recursive_wild(&new_wu);
	}
	else if (!wu->split[*wu->i + 1])
		ft_add_wild(wu->head, ft_new_wild(path, wu->c));
}

void	recursive_wild(t_wu *wu)
{
	DIR	*opened;

	if (!wu->split[*wu->i])
	{
		ft_add_wild(wu->head, ft_new_wild(wu->dir, wu->c));
		return ;
	}
	opened = opendir(wu->dir);
	if (!opened)
		return ;
	wu->entry = readdir(opened);
	while ((wu->entry))
	{
		if (current_dir(wu->entry->d_name))
			continue ;
		if (ft_chrstr('*', wu->split[*wu->i]))
			handle_wildcard_match(wu);
		else
			handle_exact_match(wu);
		wu->entry = readdir(opened);
	}
	closedir(opened);
}
