/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hundler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:19:28 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/14 15:59:28 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_dollar_only(char *arg, char *next_arg, t_c *c,
		t_arg **min_head)
{
	char	**new_args;
	int		j;

	j = 0;
	new_args = ft_args_split(expand(arg, next_arg, c), c->garbage);
	if (!new_args)
		return ;
	while (new_args[j])
	{
		if (j == 0)
			ft_add_arg(min_head, ft_new_arg(new_args[j], START, c));
		else if (new_args[j + 1] == NULL)
			ft_add_arg(min_head, ft_new_arg(new_args[j], END, c));
		else
			ft_add_arg(min_head, ft_new_arg(new_args[j], NORMAL, c));
		j++;
	}
}

char	**extact_res(char *cut, char **line, t_c *c)
{
	char	*pid;
	char	*txpandat;

	if (ft_chrstr('?', cut))
		*line = ft_addstr(*line, ft_itoa(set_status(c->status, 0), c->garbage),
				c);
	else if (!ft_strcmp(cut, "$"))
		*line = ft_addstr(*line, cut, c);
	else if (!ft_strcmp(cut, "$$"))
	{
		pid = ft_strip('\n', c->pid, c->garbage);
		*line = ft_addstr(*line, pid, c);
	}
	else
	{
		txpandat = ft_getenv(ft_strip('$', cut, c->garbage), c->ft_env);
		if (txpandat)
			*line = ft_addstr(*line, txpandat, c);
	}
	return (line);
}

int	process_dollar_expansion(char *arg, int j, t_c *c, char **line)
{
	int		k;
	char	*cut;

	k = j + 1;
	if (ft_isdigit(arg[k]) || ft_chrstr(arg[k], "$#@!^&*?"))
		k++;
	else if (ft_isalnum(arg[k]) || arg[k] == '_')
		while (arg[k] && (ft_isalnum(arg[k]) || arg[k] == '_'))
			k++;
	cut = ft_substr(arg, j, k - j, c->garbage);
	line = extact_res(cut, line, c);
	return (k);
}

char	**hundler(char **args, t_c *c, int i)
{
	t_arg	*min_head;
	char	**new;

	min_head = NULL;
	new = NULL;
	while (args[i])
	{
		if (has_qoute(args[i]) && !has_dollar(args[i]))
			args[i] = remove_qoutes(args[i], c);
		else if (!has_qoute(args[i]) && has_dollar(args[i]))
		{
			handle_dollar_only(args[i], decide(args, i), c, &min_head);
			i++;
			continue ;
		}
		else if (has_qoute(args[i]) && has_dollar(args[i]))
			args[i] = handle_dollar_in_quotes(args[i], c);
		ft_add_arg(&min_head, ft_new_arg(args[i], START, c));
		i++;
	}
	if (min_head)
		new = convert_flag(&min_head, c);
	return (new);
}
