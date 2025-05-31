/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:48:18 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/31 15:53:11 by moel-oua         ###   ########.fr       */
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
