/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:53:38 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/09 14:28:08 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	is_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && i == 0)
		{
			i++;
			continue ;
		}
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '-'))
			return (false);
		i++;
	}
	return (true);
}

static void helper(t_env **ft_env, t_gc **gc, int status)
{
	free_garbage(gc);
	ft_free_env(ft_env);
	exit(status);
}

static bool check_long(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		i++;
		len++;
	}
	if (len >= 19 && !ft_atoll(str))
		return (true);
	return (false);
}

static int exit_args(char **args, t_env **ft_env, t_gc **gc, int status)
{
	int len;

	len = args_len(args);
	if (len > 1)
	{
		if (!is_valid(args[1]) || check_long(args[1]))
		{
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			helper(ft_env, gc, 2);
		}
		if (len > 2)
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
	}
	else
		helper(ft_env, gc, 0);
	return (status);
}

int ft_exit(char **args, t_env **ft_env, t_gc **gc, int prev)
{
	int status;
	int tmp;

	status = prev;
	if (!status)
	{
		tmp = status;
		status = exit_args(args, ft_env, gc, status);
		if (status != tmp)
		{
			printf("hello %d\n", status);
			return (status);
		}
	}
	status = ft_atoll(args[1]);
	helper(ft_env, gc, status % 256);
	return (1);
}
