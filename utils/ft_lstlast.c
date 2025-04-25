/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:27:00 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/25 21:05:06 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tk *ft_lstlast(t_tk *root)
{
    t_tk *last;

    if (!root)
        return (NULL);
    last = root;
    while (last->next)
        last = last->next;
    return (last);
}

t_redic *ft_lstlast_redic(t_redic *root)
{
    t_redic *last;

    if (!root)
        return (NULL);
    last = root;
    while (last->next)
        last = last->next;
    return (last);
}