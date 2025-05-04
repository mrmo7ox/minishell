/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:14:42 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/04 11:01:32 by moel-oua         ###   ########.fr       */
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

void	replace_expandable(t_part **res, t_env **ft_env, t_gc **garbage)
{
	t_part	*curr;
	char	*new;

	curr = *res;
	while (curr)
	{
		if (curr->expandable)
		{
			new = ft_getenv(ft_strip('$', curr->content, garbage), ft_env);
			curr->content = new;
		}
		curr = curr->next;
	}
}

void	strip_both_quotes(t_part *curr, t_gc **garbage)
{
	curr->content = ft_strip('\'', curr->content, garbage);
	curr->content = ft_strip('\"', curr->content, garbage);
}

void	remove_qoute(t_part **head, t_gc **garbage)
{
	t_part	*curr;

	curr = *head;
	while (curr)
	{
		if (who_is_open(curr->content) == 1 && !curr->expandable)
			remove_double_quotes(&curr, garbage);
		else if (who_is_open(curr->content) == 2 && !curr->expandable)
			remove_single_quotes(&curr, garbage);
		else if ((ft_chrcount(curr->content, '\"') || ft_chrcount(curr->content,
					'\'')) && !curr->expandable)
		{
			strip_both_quotes(curr, garbage);
			curr = curr->next;
		}
		else
			curr = curr->next;
	}
}

void	expander(t_tk *token, t_gc **garbage, t_env **ft_env)
{
	t_expander	res;
	char		*joined;
	t_part		*curr;

	if (!token && !(token->token))
		return ;
	res = split_expand(token->token, garbage);
	if (res.result)
		replace_expandable(&(res.result), ft_env, garbage);
	remove_qoute(&(res.result), garbage);
	curr = res.result;
	joined = NULL;
	while (curr)
	{
		joined = ft_strjoin(joined, curr->content, garbage);
		curr = curr->next;
	}
	token->token = joined;
	printf("[%s]\n", token->token);
}
