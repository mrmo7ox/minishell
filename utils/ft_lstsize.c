/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:10:41 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/02 09:22:38 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_tk *head)
{
	int	i;

	if (!head)
		return (0);
	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

int	ft_args_size(t_arg *head)
{
	int	i;

	if (!head)
		return (0);
	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

int	ft_args_size_flag(t_arg *head)
{
	int	i;

	i = 0;
	if (!head)
		return (0);
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

int	ft_envsize(t_env *head)
{
	int	i;

	if (!head)
		return (0);
	i = 0;
	while (head)
	{
		if (head->value)
			i++;
		head = head->next;
	}
	return (i);
}
