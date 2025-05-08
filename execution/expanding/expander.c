/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:14:42 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/08 17:27:10 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_qoutes	*is_dollar_in_quotes(t_qoutes **quotes, int index)
{
	t_qoutes	*curr;

	(void)index;
	curr = *quotes;
	while (curr)
	{
		// if (curr->type == DQOUTE && index > curr->open_index
		// 	&& index < curr->close_index)
		// 	return (curr);
		curr = curr->next;
	}
	return (curr);
}

t_qoutes	*is_im_quotes(t_qoutes **quotes, int index)
{
	t_qoutes	*curr;

	curr = *quotes;
	while (curr)
	{
		if (curr->type == DQOUTE && (index == curr->open_index
				|| index == curr->close_index))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

t_expand	*is_index_on_dollar(t_expand **dollars, int index)
{
	t_expand	*curr;

	curr = *dollars;
	while (curr)
	{
		if (index == curr->start)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

char	*remove_quotes_and_expand(char *line, t_list *utils, t_gc **garbage,
		t_env **ft_env)
{
	char		*new;
	char		*holder;
	t_expand	*start_end;
	int			i;
	int			len;

	new = NULL;
	i = 0;
	while (line[i])
	{
		start_end = is_index_on_dollar(utils->expand, i);
		if (start_end && is_dollar_in_quotes(utils->qoutes, i))
		{
			len = start_end->end - start_end->start;
			holder = ft_strip('$', ft_copy(line + start_end->start, len,
						garbage), garbage);
			new = ft_strjoin(new, ft_getenv(holder, ft_env), garbage);
			i += len;
			continue ;
		}
		// else if (!is_im_quotes(utils->qoutes, i))
		else
		{
			new = ft_strjoin(new, ft_copy(line + i, 1, garbage), garbage);
		}
		i++;
	}
	printf("[%s]\n", new);
	return (new);
}

void	expander(t_tk *token, t_gc **garbage, t_env **ft_env)
{
	t_list	tmp;
	char	*new;

	if (!token || !token->token)
		return ;
	tmp = split_expand(token->token, garbage, ft_env);
	new = remove_quotes_and_expand(token->token, &tmp, garbage, ft_env);
}
