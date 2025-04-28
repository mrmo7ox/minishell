/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:39:28 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/28 12:36:34 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export_sort(t_env **ft_env)
{
	char	*tmp;
	t_env	*head;
	t_env	*head2;

	head = *ft_env;
	while (head)
	{
		head2 = head->next;
		while (head2)
		{
			if (strcmp(head2->name, head->name) < 0)
			{
				tmp = head->name;
				head->name = head2->name;
				head2->name = tmp;
				tmp = head->value;
				head->value = head2->value;
				head2->value = tmp;
			}
			head2 = head2->next;
		}
		head = head->next;
	}
}

