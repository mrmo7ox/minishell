/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:32:10 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/07 10:30:02 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	check_op(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (!str[i] && i > 1)
			return (true);
		return (false);
	}
	return (false);
}

int	echo(char **args)
{
	int	i;
	int	flag;
	int	count;

	flag = 0;
	i = 1;
	count = 0;
	while (args[i])
	{
		if (i == 1 && check_op(args[i]))
		{
			flag = 1;
			while (args[i] && check_op(args[i]))
				i++;
		}
		else
		{
			if (count > 0)
				printf(" ");
			printf("%s", args[i++]);
			count++;
		}
	}
	if (!flag)
		printf("\n");
	return (0);
}
