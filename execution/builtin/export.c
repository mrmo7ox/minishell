/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:50:33 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/29 14:25:30 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool syntax(char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		if (!args[i][0])
			return (false);
		i++;
	}
	return (true);
}

static void	no_args(t_env **env)
{
	t_env	*head;

	head = *env;
	while (head)
	{
		if (!strcmp(head->name, "_"))
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
}

static void	helper(char **args, t_env **ft_env, t_gc **gg)
{
	char	**tmp;
	int		i;
	char	*name;
	char	*value;

	i = 1;
	while (args[i])
	{
		if (ft_chrstr('=', args[i]) && ft_strlen(args[i]) == 1)
		{
			ft_putstr_fd(args[i] , 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			i++;
			continue ;
		}
		tmp = export_split(args[i], gg);
		name = tmp[0];
		if (ft_chrstr('=', args[i]) && !tmp[1])
			value = ft_strdup("", gg);
		else
			value = tmp[1];
		ext_export(name, value, ft_env, gg);
		i++;
	}
}

void	export(char **args, t_env **ft_env, t_gc **gg)
{
	int	len;

	export_sort(ft_env);
	len = args_len(args);
	if (len == 1)
		no_args(ft_env);
	else if (len >= 2)
	{
		if (!syntax(args))
		{
			ft_putstr_fd("bad args sysntax\n", 2);
			return ;
		}
		helper(args, ft_env, gg);
	}
}
// TODO handle : test=hh= +=
