/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:14:42 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/30 16:05:52 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// ne wcode

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
char	**convert_flag(t_arg **args, t_c *c)
{
	t_arg	*tmp;
	char	*line;
	int		i;
	char	**new;
	int		count;

	if (!args || !*args)
		return (NULL);
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
	count = 0;
	tmp = *args;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	new = ft_malloc((count + 1) * sizeof(char *), c->garbage);
	tmp = *args;
	i = 0;
	while (tmp)
	{
		new[i++] = tmp->arg;
		tmp = tmp->next;
	}
	new[i] = NULL;
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
char	*expand(char *arg, char *next, t_c *c)
{
	char	*new;
	int		i;
	int		j;
	char	*cut;
	char	*pid;
	char	*txpandat;

	new = ft_strdup("", c->garbage);
	i = 0;
	if (!ft_strcmp("$", arg) && next && has_qoute(next))
		return (new);
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			j = i + 1;
			if (ft_isdigit(arg[j]) || ft_chrstr(arg[j], "$#@!^&*?"))
				j++;
			else if (ft_isalnum(arg[j]) || arg[j] == '_')
			{
				while (arg[j] && (ft_isalnum(arg[j]) || arg[j] == '_'))
				{
					j++;
				}
			}
			cut = ft_substr(arg, i, j - i, c->garbage);
			if (ft_chrstr('?', cut))
			{
				new = ft_addstr(new, ft_itoa(set_status(c->status, 0),
							c->garbage), c);
			}
			else if (!ft_strcmp("$", cut))
			{
				new = ft_addstr(new, cut, c);
			}
			else if (!ft_strcmp("$$", cut))
			{
				pid = ft_strip('\n', c->pid, c->garbage);
				new = ft_addstr(new, pid, c);
			}
			else
			{
				printf("439 [%s]\n", cut);
				txpandat = ft_getenv(ft_strip('$', cut, c->garbage), c->ft_env);
				if (txpandat)
				{
					printf("302 ======[TEST]======\n");
					new = ft_addstr(new, txpandat, c);
				}
			}
			i = j;
			continue ;
		}
		new = ft_addchr(new, arg[i], c);
		i++;
	}
	return (new);
}

t_list	*init_list(char *arg, t_c *c)
{
	t_list		*u;
	t_expand	*dollars;
	t_qoutes	*qoutes;

	u = ft_malloc(sizeof(t_list), c->garbage);
	qoutes = NULL;
	dollars = NULL;
	u->expand = &dollars;
	u->qoutes = &qoutes;
	u->i = 0;
	u->j = 0;
	u->line = arg;
	get_quote_index(u, c->garbage);
	get_expand_index(u, c->garbage);
	return (u);
}

char	**hundler(char **args, t_c *c)
{
	t_arg		*min_head;
	int			i;
	int			j;
	char		**new;
	char		**new_args;
	t_expand	*expands;
	t_qoutes	*qoutes;
	t_list		*u;
	t_dollar	type;
	t_expand	*data;
	char		*line;
	int			k;
	char		*cut;
	t_arg		*tmp;
	char		*next;
	char		*pid;
	char		*txpandat;

	new_args = NULL;
	new = NULL;
	i = 0;
	j = 0;
	cut = NULL;
	min_head = NULL;
	while (args[i])
	{
		if (has_qoute(args[i]) && !has_dollar(args[i]))
		{
			args[i] = remove_qoutes(args[i], c);
		}
		else if (!has_qoute(args[i]) && has_dollar(args[i]))
		{
			j = 0;
			next = NULL;
			if (args[i + 1] != NULL)
				next = args[i + 1];
			new_args = ft_args_split(expand(args[i], next, c), c->garbage, 0,
					0);
			if (!new_args)
			{
				i++;
				continue ;
			}
			while (new_args[j])
			{
				if (j == 0)
				{
					ft_add_arg(&min_head, ft_new_arg(new_args[j], START, c));
				}
				else if (new_args[j + 1] == NULL)
				{
					ft_add_arg(&min_head, ft_new_arg(new_args[j], END, c));
				}
				else
				{
					ft_add_arg(&min_head, ft_new_arg(new_args[j], NORMAL, c));
				}
				j++;
			}
			i++;
			continue ;
		}
		else if (has_qoute(args[i]) && has_dollar(args[i]))
		{
			line = ft_strdup("", c->garbage);
			j = 0;
			u = init_list(args[i], c);
			expands = *u->expand;
			qoutes = *u->qoutes;
			while (args[i][j])
			{
				type = is_dollar_in_quotes(&qoutes, j);
				data = is_index_on_dollar(&expands, j);
				if ((args[i][j] == '$' || data) && type == INSIDED)
				{
					if (args[i][j] == '$')
					{
						k = j + 1;
						if (ft_isdigit(args[i][k]) || ft_chrstr(args[i][k],
								"$#@!^&*?"))
						{
							k++;
						}
						else if (ft_isalnum(args[i][k]) || args[i][k] == '_')
						{
							while (args[i][k] && (ft_isalnum(args[i][k])
									|| args[i][k] == '_'))
							{
								k++;
							}
						}
						cut = ft_substr(args[i], j, k - j, c->garbage);
						if (ft_chrstr('?', cut))
						{
							line = ft_addstr(line, ft_itoa(set_status(c->status,
											0), c->garbage), c);
						}
						else if (!ft_strcmp(cut, "$"))
						{
							line = ft_addstr(line, cut, c);
						}
						else if (!ft_strcmp(cut, "$$"))
						{
							pid = ft_strip('\n', c->pid, c->garbage);
							line = ft_addstr(line, pid, c);
						}
						else
						{
							printf("439 [%s]\n", cut);
							txpandat = ft_getenv(ft_strip('$', cut, c->garbage),
									c->ft_env);
							if (txpandat)
							{
								printf("======[TEST]======\n");
								line = ft_addstr(line, txpandat, c);
							}
						}
						j = k;
						continue ;
					}
				}
				else if (is_im_quotes(&qoutes, j))
				{
					j++;
					continue ;
				}
				line = ft_addchr(line, args[i][j], c);
				j++;
			}
			args[i] = line;
		}
		ft_add_arg(&min_head, ft_new_arg(args[i], START, c));
		i++;
	}
	if (min_head)
	{
		new = convert_flag(&min_head, c);
	}
	return (new);
}

char	**expander(char **args, t_c *c)
{
	int		i;
	char	**new;
	t_arg	*head;
	t_arg	*tmp;
	char	**splited;
	int		j;

	new = NULL;
	head = NULL;
	i = 0;
	if (!args)
		return (NULL);
	while (args[i])
	{
		if (has_qoute(args[i]) && !has_dollar(args[i]))
			args[i] = remove_qoutes(args[i], c);
		else if (!has_qoute(args[i]) && has_dollar(args[i]))
		{
			j = 0;
			splited = ft_args_split(expand(args[i], NULL, c), c->garbage, 0, 0);
			if (!splited)
				return (NULL);
			while (splited[j])
			{
				ft_add_arg(&head, ft_new_arg(splited[j], NORMAL, c));
				j++;
			}
			i++;
			continue ;
		}
		else if (has_qoute(args[i]) && has_dollar(args[i]))
		{
			splited = ft_expand_split(args[i], c, 0, 0);
			splited = hundler(splited, c);
			if (!splited)
			{
				i++;
				continue ;
			}
			j = 0;
			while (splited[j])
			{
				ft_add_arg(&head, ft_new_arg(splited[j], NORMAL, c));
				j++;
			}
			i++;
			continue ;
		}
		ft_add_arg(&head, ft_new_arg(args[i], NORMAL, c));
		i++;
	}
	if (head)
	{
		new = ft_malloc(sizeof(char *) * (ft_args_size(head) + 1), c->garbage);
		if (!new)
			return (NULL);
		convert(&head, new);
	}
	return (new);
}
