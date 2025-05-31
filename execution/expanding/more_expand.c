/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:53:46 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/31 16:17:27 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	convert(t_arg **args, char **new)
{
	t_arg	*tmp;
	int		i;

	i = 0;
	if (!args || !new)
		return ;
	tmp = *args;
	while (tmp)
	{
		new[i] = tmp->arg;
		tmp = tmp->next;
		i++;
	}
	new[i] = NULL;
}

char	**convert_(char *line, t_c *c)
{
	char	**new;

	new = ft_malloc(sizeof(char *) * 2, c->garbage);
	new[0] = line;
	new[1] = NULL;
	return (new);
}

bool	has_qoute(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '"' || arg[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

bool	has_dollar(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

char	*remove_qoutes(char *arg, t_c *c)
{
	char	*new;
	int		i;
	char	qoute;

	new = ft_strdup("", c->garbage);
	i = 0;
	while (arg[i])
	{
		if (ft_chrstr(arg[i], "\'\""))
		{
			qoute = arg[i];
			i++;
			while (arg[i] && arg[i] != qoute)
			{
				new = ft_addchr(new, arg[i], c);
				i++;
			}
			if (arg[i] == qoute)
				i++;
			continue ;
		}
		new = ft_addchr(new, arg[i], c);
		i++;
	}
	return (new);
}
