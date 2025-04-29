/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:39:28 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/29 15:12:03 by ihamani          ###   ########.fr       */
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
			if (ft_strcmp(head2->name, head->name) < 0)
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

char	**export_split(char *str, t_gc **gg)
{
	size_t	i;
	size_t	pos;
	char	**args;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	pos = i;
	if (pos == ft_strlen(str))
	{
		args = ft_malloc((2 * sizeof(char *)), gg);
		args[0] = ft_strdup(str, gg);
		args[1] = NULL;
	}
	else
	{
		args = ft_malloc((3 * sizeof(char *)), gg);
		args[0] = ft_substr(str, 0, pos, gg);
		args[1] = ft_substr(str, pos + 1, (strlen(str) - pos), gg);
		args[2] = NULL;
	}
	return (args);
}
