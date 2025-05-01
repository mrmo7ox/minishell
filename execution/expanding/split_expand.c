/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:47:41 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/01 12:00:18 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_expander	*split_expand(char *line, t_gc **garbage)
{
	int qouat_count;
	t_expander utils;
	utils.i = 0;
	utils.j = 0;

	qouat_count = 0;
	while (line[i])
	{
		if (line[utils.i] == '"')
			qouat_count++;
		else if (line[utils.i] == '$')
		{
			utils.j = utils.i;
			while (line[utils.i] != ' ')
				utils.i++;
			utils.target = ft_copy(line + utils.j, utils.i, )
		}
		(utils.i)++;
	}
	printf("%d\n", qouat_count);
}