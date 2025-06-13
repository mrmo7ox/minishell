/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:22:54 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/31 21:36:09 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_quotes_only(char *arg, t_c *c, t_arg **head)
{
	arg = remove_qoutes(arg, c);
	if (!arg || !*arg)
		ft_add_arg(head, ft_new_arg(ft_strdup("", c->garbage), NORMAL, c));
	else
		ft_add_arg(head, ft_new_arg(arg, NORMAL, c));
}
