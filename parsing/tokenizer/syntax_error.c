/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nero <nero@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:44:49 by moel-oua          #+#    #+#             */
/*   Updated: 2025/03/17 17:40:23 by nero             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	syntax_error(char *line)
{
	int	i;

	i = 0;
	if (!qoutes(line) || !and_or(line)
		|| !parenthesis(line, &i, 0)
		|| !redir_handler(line))
		perror("syntax error\n");
	return (true);
}
