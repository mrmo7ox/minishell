/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:14:00 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/15 10:30:15 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handle_special_cases(char *cut, t_c *c)
{
	char	*expanded;

	if (ft_chrstr('?', cut))
	{
		expanded = ft_itoa(set_status(c->status, 0), c->garbage);
	}
	else if (!ft_strcmp("$", cut))
	{
		expanded = cut;
	}
	else if (!ft_strcmp("$$", cut))
	{
		expanded = ft_strip('\n', c->pid, c->garbage);
	}
	else
	{
		expanded = ft_getenv(ft_strip('$', cut, c->garbage), c->ft_env);
	}
	return (expanded);
}

void	process_variable(char *arg, int *i, char **new, t_c *c)
{
	int		j;
	char	*cut;
	char	*expanded;

	j = *i + 1;
	if (ft_isdigit(arg[j]) || ft_chrstr(arg[j], "$#@!^&*?"))
		j++;
	else if (ft_isalnum(arg[j]) || arg[j] == '_')
	{
		while (arg[j] && (ft_isalnum(arg[j]) || arg[j] == '_'))
			j++;
	}
	cut = ft_substr(arg, *i, j - *i, c->garbage);
	expanded = handle_special_cases(cut, c);
	if (expanded)
		*new = ft_addstr(*new, expanded, c);
	*i = j;
}

char	*expand(char *arg, char *next, t_c *c)
{
	char	*new;
	int		i;

	new = ft_strdup("", c->garbage);
	i = 0;
	if (!ft_strcmp("$", arg) && next && has_qoute(next))
		return (new);
	while (arg[i])
	{
		if (arg[i] == '$')
			process_variable(arg, &i, &new, c);
		else
		{
			new = ft_addchr(new, arg[i], c);
			i++;
		}
	}
	return (new);
}

char	*decide(char **array, int i)
{
	if (!array || !*array)
		return (NULL);
	if (array[i + 1] != NULL)
		return (array[i + 1]);
	else
		return (NULL);
}
