/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:11:44 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/05 15:36:41 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(char **args, t_gc **gg)
{
	char	*buff;

	(void)args;
	buff = getcwd(NULL, 0);
	if (!buff)
		return (1);
	ft_add_gc(gg, ft_new_gc_node(buff));
	printf("%s\n", buff);
	return (0);
}
