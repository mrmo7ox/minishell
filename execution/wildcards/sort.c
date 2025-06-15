/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:47:03 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/15 10:10:05 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*strlow(const char *str, t_c *c)
{
	char	*new_str;
	int		i;

	new_str = NULL;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			new_str = ft_addchr(new_str, str[i] + 32, c);
		else
			new_str = ft_addchr(new_str, str[i], c);
		i++;
	}
	return (new_str);
}

void	splitit(t_wild *source, t_wild **a, t_wild **b)
{
	t_wild	*tmp;
	int		size;
	int		i;

	tmp = NULL;
	if (!source || !source->next)
	{
		*a = source;
		*b = NULL;
		return ;
	}
	*a = source;
	size = ft_wildsize(source);
	i = 0;
	while (i < size / 2 && source)
	{
		tmp = source;
		source = source->next;
		i++;
	}
	if (tmp)
		tmp->next = NULL;
	*b = source;
}

t_wild	*sortit(t_wild *a, t_wild *b, t_c *c)
{
	t_wild	*res;

	res = NULL;
	if (!a)
		return (b);
	else if (!b)
		return (a);
	if (ft_strcmp(strlow(a->arg, c), strlow(b->arg, c)) <= 0)
	{
		res = a;
		res->next = sortit(a->next, b, c);
	}
	else
	{
		res = b;
		res->next = sortit(a, b->next, c);
	}
	return (res);
}

void	merge_sorting(t_wild **head, t_c *c)
{
	t_wild	*a;
	t_wild	*b;

	if (!head || !*head || !(*head)->next)
		return ;
	splitit(*head, &a, &b);
	merge_sorting(&a, c);
	merge_sorting(&b, c);
	*head = sortit(a, b, c);
}
