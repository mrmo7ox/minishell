/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:50:33 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/31 12:54:29 by ihamani          ###   ########.fr       */
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

static void	no_args(t_env **ft_env, int out)
{
	t_env	*head;
	t_env	*tmp;

	tmp = NULL;
	clone_env(ft_env, &tmp);
	export_sort(&tmp);
	head = tmp;
	no_args_ext(head, out);
	free_tmp(&tmp);
}

static void	helper(char **args, t_env **ft_env, t_gc **gc, int *status)
{
	char	**tmp;
	int		i[2];
	char	*value;

	i[0] = 1;
	while (args[i[0]])
	{
		if ((ft_chrstr('=', args[i[0]]) && ft_strlen(args[i[0]]) == 1)
			|| args[i[0]][0] == '=')
		{
			ft_putstr_fd(args[i[0]++], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			*status = 1;
			continue ;
		}
		tmp = export_split(args[i[0]]);
		if (ft_chrstr('=', args[i[0]++]) && !tmp[1])
			value = "";
		else
			value = tmp[1];
		i[1] = ext_export(tmp[0], value, ft_env, gc);
		if (i[1])
			*status = i[1];
		free_d(tmp);
	}
}

int	export(char **args, int out, t_env **ft_env, t_gc **gc)
{
	int	len;
	int	status;

	status = 0;
	len = args_len(args);
	if (out == 0)
		out = 1;
	else if (out < 0)
		return (1);
	if (len == 1)
		no_args(ft_env, out);
	else if (len >= 2)
	{
		if (!syntax(args))
		{
			ft_putstr_fd("bad args sysntax\n", 2);
			return (1);
		}
		helper(args, ft_env, gc, &status);
	}
	return (status);
}
