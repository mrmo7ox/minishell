/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:50:33 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/28 12:37:40 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	syntax(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (!args[i][0])
			return (false);
		while (args[i][j])
		{
			if (args[i][j] == '=' && j == 0)
				return (false);
			j++;
		}
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

static void	helper(char **args, t_env **ft_env)
{
	char	**tmp;
	int		i;
	char	*name;
	char	*value;

	i = 1;
	while (args[i])
	{
		tmp = ft_minisplit(args[i], '=', 0, 0);
		name = tmp[0];
		value = tmp[1];
		ext_export(name, value, ft_env, tmp);
		free(tmp);
		i++;
	}
}

void	export(char **args, t_env **ft_env)
{
	int		len;

	len = args_len(args);
	if (!syntax(args))
	{
		ft_putstr_fd("bad args sysntax\n", 2);
		return ;
	}
	export_sort(ft_env);
	if (len == 1)
		no_args(ft_env);
	else if (len >= 2)
		helper(args, ft_env);
}
// TODO sort env before printing
// int main(int ac, char **av, char **env)
//  {
//  	t_env	*ft_env = NULL;

//  	env_init(env, &ft_env);
//  	export(av, &ft_env);
//  	// no_args(&ft_env);
// }
