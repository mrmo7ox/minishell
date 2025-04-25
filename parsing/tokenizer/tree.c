/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:15:33 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/25 10:58:39 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_leaf *new_leaf(t_tk *token, e_type type)
{
	t_leaf *new = malloc(sizeof(t_leaf));
	if (!new)
		return NULL;

	new->type = type;
	new->token = token;
	new->left = NULL;
	new->right = NULL;

	return new;
}