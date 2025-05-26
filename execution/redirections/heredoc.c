/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:02:33 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/26 15:33:48 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_heredoc(t_tk *token, t_container *c)
{
	t_redic		*curr;

	curr = token->redics;
	token->heredoc = 0;
	token->is_last = 0;
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			if (!heredoc(token, ft_strip('<', curr->content, c->garbage), c))
				return ;
			if (curr->next == NULL)
				token->is_last = 1;
		}
		curr = curr->next;
	}
}

void	check_iflast(t_tk *token)
{
	if (token->is_last)
	{
		if (token->in >= 0)
		{
			if (token->in > 0)
				close(token->in);
			token->in = token->heredoc;
		}
		else
		{
			if (token->heredoc > 0)
				close(token->heredoc);
		}
	}
	else
	{
		if (token->heredoc > 0)
			close(token->heredoc);
	}
}
