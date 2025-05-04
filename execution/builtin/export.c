/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:50:33 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/03 11:04:59 by moel-oua         ###   ########.fr       */
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
		free(head);
		head = nt;
	}
	*tmp = NULL;
}

static void	no_args(t_env **ft_env, t_gc **gc)
{
	t_env	*head;
	t_env	*tmp;

	tmp = NULL;
	clone_env(ft_env, &tmp, gc);
	export_sort(&tmp);
	head = tmp;
	while (head)
	{
		if (!ft_strcmp(head->name, "_"))
		{
			head = head->next;
			continue ;
		}
		printf("declare -x %s", head->name);
		if (head->value)
			printf("=\"%s\"\n", head->value);
		else
			printf("\n");
		head = head->next;
	}
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
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			i++;
			continue ;
		}
		tmp = export_split(args[i]);
		name = tmp[0];
		if (ft_chrstr('=', args[i]) && !tmp[1])
			value = ft_strdup("", gc);
		else
			value = tmp[1];
		ext_export(name, value, ft_env, gc);
		i++;
	}
}

void	export(char **args, t_env **ft_env, t_gc **gc)
{
	int	len;

	len = args_len(args);
	if (len == 1)
		no_args(ft_env, gc);
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
