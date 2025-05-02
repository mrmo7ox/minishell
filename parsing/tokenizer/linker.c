/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:26:19 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/01 14:08:34 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	linker(t_leaf **root, void (*applyme)(t_tk *token, t_gc **garbage),
		t_gc **garbage)
{
	t_leaf	*tmp;

	if (!root || !(*root))
		return ;
	tmp = *root;
	if (tmp->right)
	{
		if (tmp->right->type == COMMAND)
		{
			if (tmp->right->token && ft_strinstr(tmp->right->token->token, "$"))
			{
				applyme(tmp->right->token, garbage);
			}
		}
		else
			linker(&(tmp->right), applyme, garbage);
	}
	if (tmp->left)
	{
		if (tmp->left->type == COMMAND)
		{
			if (tmp->left->token && ft_strinstr(tmp->left->token->token, "$"))
				applyme(tmp->left->token, garbage);
		}
		else
			linker(&(tmp->left), applyme, garbage);
	}
}
