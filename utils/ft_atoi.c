/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:28:54 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/08 16:58:22 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_overflow(long long r, long long t, int s)
{
	return ((s == 1 && (r < t || r > INT_MAX))
		|| (s == -1 && ((s * r) > (s * t) || (s * r) < INT_MIN)));
}

int	ft_atoi(char *str)
{
	int					i;
	int					s;
	long long			r;
	long long			t;

	i = 0;
	r = 0;
	s = 1;
	t = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		r = (r * 10) + (str[i++] - '0');
		if (check_overflow(r, t, s))
			return (0);
		t = r;
	}
	return (r * s);
}
