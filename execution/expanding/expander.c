/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:14:42 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/03 14:04:57 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	who_is_open(char *line)
{
	if (!line)
		return (0);
	if (ft_chrcount(line, '\'') && ft_chrcount(line, '\"'))
	{
		if (ft_chrindex(line, '\'') > ft_chrindex(line, '\"'))
			return (1);
		else if (ft_chrindex(line, '\'') < ft_chrindex(line, '\"'))
			return (2);
	}
	return (0);
}

void	expander(t_tk *token, t_gc **garbage, t_env **ft_env)
{
	t_expander res;
	char *new;
	char *joined = NULL;
	if (token && token->token)
	{
		res = split_expand(token->token, garbage);
		t_part *curr;

		curr = res.result;
		while (curr)
		{
			if (curr->expandable)
			{
				new = ft_getenv(ft_strip('$', curr->content, garbage), ft_env);
				curr->content = new;
			}
			curr = curr->next;
		}
		curr = res.result;
		while (curr)
		{
			if (who_is_open(curr->content) == 1 && !curr->expandable)
			{
				if (ft_chrcount(curr->content, '\"') % 2 == 0)
				{
					curr->content = ft_strip('\"', curr->content, garbage);
					curr = curr->next;
					continue ;
				}
				curr->content = ft_strip('\"', curr->content, garbage);
				while (curr && !ft_chrstr('\"', curr->content))
				{
					curr = curr->next;
				}
				curr->content = ft_strip('\"', curr->content, garbage);
				curr = curr->next;
				continue ;
			}
			else if (who_is_open(curr->content) == 2 && curr->expandable == 0)
			{
				if (ft_chrcount(curr->content, '\'') % 2 == 0)
				{
					curr->content = ft_strip('\'', curr->content, garbage);
					curr = curr->next;
					continue ;
				}
				curr->content = ft_strip('\'', curr->content, garbage);
				while (curr && !ft_chrstr('\'', curr->content))
				{
					curr = curr->next;
				}
				curr->content = ft_strip('\'', curr->content, garbage);
				curr = curr->next;
				continue ;
			}
			else if ((ft_chrcount(curr->content, '\"')
					|| ft_chrcount(curr->content, '\'')) && !curr->expandable)
			{
				curr->content = ft_strip('\'', curr->content, garbage);
				curr->content = ft_strip('\"', curr->content, garbage);
			}
			// printf("%s\n", curr->content);
			// if (ft_strinstr(curr->content, "$@$"))
			// {
			// 	curr->content = ft_strdup(" ", garbage);
			// }
			curr = curr->next;
		}
		curr = res.result;
		printf("=====[sper]=====\n");
		while (curr)
		{
			joined = ft_strjoin(joined, curr->content, garbage);
			curr = curr->next;
		}
		printf("[%s]\n", joined);
	}
}