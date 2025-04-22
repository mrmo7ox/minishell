/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:32:10 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/22 14:13:15 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool check_op(char *str)
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

int main(int ac, char **av)
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
