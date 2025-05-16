/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:32:10 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/16 16:31:52 by ihamani          ###   ########.fr       */
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

static void	helper(char **args, int out, int flag, int count)
{
	int	i;

	i = 1;
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
				ft_putstr_fd(" ", out);
			ft_putstr_fd(args[i++], out);
			count++;
		}
	}
	if (!flag)
		ft_putstr_fd("\n", out);
}

int	echo(char **args, int out)
{
	if (out == 0)
		out = 1;
	else if (out < 0)
		return (1);
	helper(args, out, 0, 0);
	return (0);
}
