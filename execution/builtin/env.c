/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:50:35 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/11 10:01:14 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cmd_env(char **args, int out, t_env **env)
{
	t_env	*head;
	int		len;

	len = args_len(args);
	if (len > 1)
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
	if (!out)
		out = 1;
	head = *env;
	while (head)
	{
		if (head->value)
		{
			ft_putstr_fd(head->name, out);
			ft_putstr_fd("=", out);
			ft_putstr_fd(head->value, out);
			ft_putstr_fd("\n", out);
		}
		head = head->next;
	}
	return (0);
}
