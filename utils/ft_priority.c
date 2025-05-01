/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_priority.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:10:17 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/29 16:16:43 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_priority(char *token)
{
	if (token && ft_strstr(token, "||"))
		return (3);
	else if (token && ft_strstr(token, "&&"))
		return (2);
	else if (token && ft_strstr(token, "|"))
		return (1);
	return (0);
}