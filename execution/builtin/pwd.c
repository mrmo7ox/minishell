/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:11:44 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/29 11:09:36 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *pwd(t_gc **gg)
{
	char *buff;

	buff = getcwd(NULL, 0);
	if (!buff)
		return (NULL);
	ft_add_gc(gg, ft_new_gc_node(buff));
	printf("%s\n", buff);
	return (buff);
}