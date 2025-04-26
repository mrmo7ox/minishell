/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:32:10 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/26 16:30:56 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool check_op(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while(str[i] == 'n')
			i++;
		if (!str[i] && i > 1)
			return (true);
		return (false);
	}
	return (false);
}

void	echo(int ac, char **av)
{
	int i;
	int flag;
	int	count;

	flag = 0;
	i = 1;
	count = 0;
	while (i < ac)
	{
		if (i == 1 && check_op(av[i]))
		{
			flag = 1;
			while (i < ac && check_op(av[i]))
				i++;
		}
		else
		{
			if (count > 0)
				printf(" ");
			printf("%s", av[i]);
			count++;
			i++;
		}
	}
	if (!flag)
		printf("\n");
}
