/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:50:35 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/01 10:27:12 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmd_env(char **args, t_env **env)
{
	t_env	*head;
	int		len;

	len = args_len(args);
	if (len > 1)
	{
		ft_putstr_fd("too many arguments", 2);
		return ;
	}
	head = *env;
	while (head->next)
	{
		if (head->value)
			printf("%s=%s\n", head->name, head->value);
		head = head->next;
	}
}
