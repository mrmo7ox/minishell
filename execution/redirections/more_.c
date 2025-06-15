/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:48:18 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/15 10:10:26 by moel-oua         ###   ########.fr       */
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

bool	have_white(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_whitespaces(str[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	check_amb(char *new)
{
	int	i;

	i = 0;
	while (new[i] == '*')
		i++;
	if (!new[i])
		return (false);
	i = 0;
	while (new[i])
	{
		while (new[i] && ft_whitespaces(new[i]))
			i++;
		if (!new[i])
			return (false);
		while (new[i] && new[i] != ' ')
			i++;
		while (new[i] && ft_whitespaces(new[i]))
			i++;
		if (new[i])
			return (false);
	}
	return (true);
}
