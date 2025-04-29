/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:11:44 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/29 14:38:19 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_pwd(char **args, t_gc **gg)
{
	char	*buff;
	int		len;

	len = args_len(args);
	if (len > 1)
		ft_putstr_fd("too many arguments", 2);
	buff = getcwd(NULL, 0);
	if (!buff)
		return (NULL);
	ft_add_gc(gg, ft_new_gc_node(buff));
	printf("%s\n", buff);
	return (buff);
}
