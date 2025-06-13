/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:48:18 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/02 10:48:44 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	check_f(t_tk *token, char *path, t_c *c)
{
	if (!check_redr_file(remove_qoutes(path, c)))
	{
		token->in = -1;
		errno = 2;
		return (false);
	}
	return (true);
}

bool	check_amb(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		while (tmp[i] && ft_whitespaces(tmp[i]))
			i++;
		if (!tmp[i])
			return (false);
		while (tmp[i] && tmp[i] != ' ')
			i++;
		while (tmp[i] && ft_whitespaces(tmp[i]))
			i++;
		if (tmp[i])
			return (false);
	}
	return (true);
}
