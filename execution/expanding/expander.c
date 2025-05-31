/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:14:42 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/31 17:22:50 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_dollar_only(char *arg, t_c *c, t_arg **head)
{
	char	**splited;
	int		j;

	j = 0;
	splited = ft_args_split(expand(arg, NULL, c), c->garbage);
	splited = wildcards(splited, c);
	if (!splited)
		return ;
	while (splited[j])
	{
		ft_add_arg(head, ft_new_arg(splited[j], NORMAL, c));
		j++;
	}
}

void	handle_both_quotes_and_dollar(char *arg, t_c *c, t_arg **head)
{
	char	**splited;
	int		j;

	j = 0;
	splited = ft_expand_split(arg, c, 0, 0);
	splited = hundler(splited, c);
	if (!splited)
		return ;
	while (splited[j])
	{
		ft_add_arg(head, ft_new_arg(splited[j], NORMAL, c));
		j++;
	}
	return ;
}

void	handle_normal_case(char *arg, t_c *c, t_arg **head)
{
	char	**splited;
	int		x;

	x = 0;
	splited = wildcards(convert_(arg, c), c);
	if (!splited)
		return ;
	while (splited[x])
	{
		ft_add_arg(head, ft_new_arg(splited[x], NORMAL, c));
		x++;
	}
	return ;
}

char	**process_args_to_list(char **args, t_c *c, t_arg **head)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (has_qoute(args[i]) && !has_dollar(args[i]))
			handle_quotes_only(args[i], c, head);
		else if (!has_qoute(args[i]) && has_dollar(args[i]))
			handle_dollar_only(args[i], c, head);
		else if (has_qoute(args[i]) && has_dollar(args[i]))
			handle_both_quotes_and_dollar(args[i], c, head);
		else
			handle_normal_case(args[i], c, head);
		i++;
	}
	if (head && *head)
		return (convert_to_array(head, c));
	else
		return (NULL);
}

char	**expander(char **args, t_c *c)
{
	t_arg	*head;

	head = NULL;
	if (!args)
		return (gen_arry(ft_strdup("", c->garbage), c->garbage));
	return (process_args_to_list(args, c, &head));
}
