/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:24:02 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/07 09:47:28 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_chrstr(char chr, char *str)
{
	if (!str)
		return (false);
	while (*str != '\0')
	{
		if (chr == *str)
			return (true);
		str++;
	}
	return (false);
}
