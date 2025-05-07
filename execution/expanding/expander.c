/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:14:42 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/07 11:59:14 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expander(t_tk *token, t_gc **garbage, t_env **ft_env)
{
	t_expander	res;
	t_list		*tmp;
	char		**l;

	if (!token && !(token->token))
		return ;
	l = ft_args_split(token->token, garbage, 0, 0);
	res = split_expand(l, garbage, ft_env);
	// tmp = *(res.result);
	// while (tmp)
	// {
	// 	printf("[%s]\n", tmp->line);
	// 	tmp = tmp->next;
	// }
}
