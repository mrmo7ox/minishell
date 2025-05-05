/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:45:04 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/05 20:24:35 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_len(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i += 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	put_in(char *p, long n, int len)
{
	int	i;

	i = len - 1;
	if (n < 0)
	{
		p[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		p[i--] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(long n, t_gc **garbage)
{
	int len;
	char *p;

	if (n == 0)
	{
		p = ft_malloc(2, garbage);
		if (p)
		{
			p[0] = '0';
			p[1] = '\0';
		}
		return (p);
	}
	len = get_len(n);
	p = ft_malloc(len + 1, garbage);
	if (!p)
		return (NULL);
	put_in(p, n, len);
	p[len] = '\0';
	return (p);
}