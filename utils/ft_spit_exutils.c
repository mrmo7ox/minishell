/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spit_exutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:22:50 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/31 14:58:25 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_hit(int *i, char *str)
{
	(*i)++;
	if (ft_isdigit(str[*i]) || ft_chrstr(str[*i], "$#@!^&*?"))
		(*i)++;
	else if (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		{
			(*i)++;
		}
	}
}

void	not_hit(int *i, char *str)
{
	char	qoute;

	while (str[*i] && !ft_chrstr(str[*i], "$"))
	{
		if (ft_chrstr(str[*i], "\"'"))
		{
			qoute = str[*i];
			(*i)++;
			while (str[*i] && str[*i] != qoute)
			{
				(*i)++;
			}
			if (qoute == str[*i])
				(*i)++;
			continue ;
		}
		(*i)++;
	}
}
