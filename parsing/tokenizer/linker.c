/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:26:19 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/01 11:19:22 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	linker(t_leaf **root, void (*applyme)(t_tk *token))
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
				expander(tmp->right->token);
		}
		else
			linker(&(tmp->right));
	}
	if (tmp->left)
	{
		if (tmp->left->type == COMMAND)
		{
			if (tmp->left->token && ft_strinstr(tmp->left->token->token, "$"))
				expander(tmp->left->token);
		}
		else
			linker(&(tmp->left));
	}
}
