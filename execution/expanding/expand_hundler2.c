/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hundler2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:21:50 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/31 17:21:29 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_start_flags(t_arg **args, t_c *c)
{
	t_arg	*tmp;
	char	*line;

	tmp = *args;
	while (tmp)
	{
		if (tmp->flag == START && tmp->prev)
		{
			line = ft_addstr(tmp->prev->arg, tmp->arg, c);
			tmp->prev->arg = line;
			tmp->prev->flag = NORMAL;
			tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			tmp = tmp->prev;
		}
		tmp = tmp->next;
	}
}

static void	handle_end_flags(t_arg **args, t_c *c)
{
	t_arg	*tmp;
	char	*line;

	tmp = *args;
	while (tmp)
	{
		if (tmp->flag == END && tmp->next)
		{
			line = ft_addstr(tmp->arg, tmp->next->arg, c);
			tmp->arg = line;
			tmp->flag = NORMAL;
			tmp->next = tmp->next->next;
			if (tmp->next)
				tmp->next->prev = tmp;
			continue ;
		}
		tmp = tmp->next;
	}
}

static int	count_args(t_arg *args)
{
	int	count;

	count = 0;
	while (args)
	{
		count++;
		args = args->next;
	}
	return (count);
}

static char	**create_arg_array(t_arg *args, int count, t_c *c)
{
	char	**new;
	int		i;

	new = ft_malloc((count + 1) * sizeof(char *), c->garbage);
	i = 0;
	while (args)
	{
		new[i++] = args->arg;
		args = args->next;
	}
	new[i] = NULL;
	return (new);
}

char	**convert_flag(t_arg **args, t_c *c)
{
	int	count;

	if (!args || !*args)
		return (NULL);
	handle_start_flags(args, c);
	handle_end_flags(args, c);
	count = count_args(*args);
	return (create_arg_array(*args, count, c));
}
