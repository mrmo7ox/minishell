/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:39:28 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/31 12:53:27 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clone_env(t_env **ft_env, t_env **tmp)
{
	t_env	*head;

	head = *ft_env;
	while (head)
	{
		ft_add_env(tmp, ft_new_env(head->name,
				head->value));
		head = head->next;
	}
}

void	export_sort(t_env **ft_env)
{
	char	*tmp;
	t_env	*head;
	t_env	*head2;

	head = *ft_env;
	while (head)
	{
		head2 = head->next;
		while (head2)
		{
			if (ft_strcmp(head2->name, head->name) < 0)
			{
				tmp = head->name;
				head->name = head2->name;
				head2->name = tmp;
				tmp = head->value;
				head->value = head2->value;
				head2->value = tmp;
			}
			head2 = head2->next;
		}
		head = head->next;
	}
}

char	**export_split(char *str)
{
	size_t	i;
	size_t	pos;
	char	**args;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	pos = i;
	if (pos == ft_strlen(str))
	{
		args = malloc((2 * sizeof(char *)));
		args[0] = ft_strdupnofree(str);
		args[1] = NULL;
	}
	else
	{
		args = malloc((3 * sizeof(char *)));
		args[0] = ft_cut(str, 0, pos);
		args[1] = ft_cut(str, pos + 1, (ft_strlen(str) - pos));
		args[2] = NULL;
	}
	return (args);
}

void	no_args_ext(t_env *head, int out)
{
	while (head)
	{
		if (!ft_strcmp(head->name, "_"))
		{
			head = head->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", out);
		ft_putstr_fd(head->name, out);
		if (head->value)
		{
			ft_putstr_fd("=\"", out);
			ft_putstr_fd(head->value, out);
			ft_putstr_fd("\"\n", out);
		}
		else
			ft_putstr_fd("\n", out);
		head = head->next;
	}
}

void	free_d(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
}
