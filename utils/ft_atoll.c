/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:12:44 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/09 14:26:26 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	ft_atoll(char *str)
{
	unsigned long long	result;
	int					sign;
	unsigned long long	max;

	result = 0;
	sign = 1;
	max = 9223372036854775807;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '-')
			sign = -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (result > (max - (*str - '0')) / 10)
			return (0);
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
