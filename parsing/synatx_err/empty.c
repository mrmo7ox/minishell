/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:19:24 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/14 10:23:21 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool    empty(char *line)
{
    char    *formated;

    formated = formating(line);
    if(ft_strlen(formated) == 0)
        return (true);
    return (false);
}