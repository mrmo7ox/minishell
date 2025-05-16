/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:50:33 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/16 16:26:35 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	syntax(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!args[i][0])
			return (false);
		i++;
	}
	return (true);
}

static void	free_tmp(t_env **tmp)
{
	t_env	*head;
	void	*nt;

	head = *tmp;
	while (head)
	{
		nt = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = nt;
	}
	*tmp = NULL;
}

static void	no_args(t_env **ft_env, int out, t_gc **gc)
{
	t_env	*head;
	t_env	*tmp;

	tmp = NULL;
	clone_env(ft_env, &tmp, gc);
	export_sort(&tmp);
	head = tmp;
	no_args_ext(head, out);
	free_tmp(&tmp);
}

static void	helper(char **args, t_env **ft_env, t_gc **gc)
{
	char	**tmp;
	int		i;
	char	*name;
	char	*value;

	i = 1;
	while (args[i])
	{
		if ((ft_chrstr('=', args[i]) && ft_strlen(args[i]) == 1)
			|| args[i][0] == '=')
		{
			ft_putstr_fd(args[i++], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			continue ;
		}
		tmp = export_split(args[i]);
		name = tmp[0];
		if (ft_chrstr('=', args[i]) && !tmp[1])
			value = "";
		else
			value = tmp[1];
		ext_export(name, value, ft_env, gc);
		free_d(tmp);
		i++;
	}
}

void	export(char **args, int out, t_env **ft_env, t_gc **gc)
{
	int	len;

	len = args_len(args);
	if (out == 0)
		out = 1;
	else if (out < 0)
		return ;
	if (len == 1)
		no_args(ft_env, out, gc);
	else if (len >= 2)
	{
		if (!syntax(args))
		{
			ft_putstr_fd("bad args sysntax\n", 2);
			return ;
		}
		helper(args, ft_env, gc);
	}
}
