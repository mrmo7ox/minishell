/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:13:35 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/02 10:50:49 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	skip_to_closing_quote(char *line, int *i, char quote)
{
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
		(*i)++;
}

static int	handle_quotes(char *line, int *i)
{
	if (line[*i] == '"')
		skip_to_closing_quote(line, i, '"');
	else if (line[*i] == '\'')
		skip_to_closing_quote(line, i, '\'');
	else
		return (0);
	return (1);
}

static int	handle_word_concat(char **new_line, t_mini *m_utils, t_gc **garbage)
{
	char	*word;
	char	*tmp;

	word = ft_copy(&m_utils->line[m_utils->j], m_utils->i - m_utils->j,
			garbage);
	if (!word)
		return (0);
	if (!*new_line)
		*new_line = ft_strdup(word, garbage);
	else
	{
		tmp = ft_strjoin(*new_line, " ", garbage);
		*new_line = ft_strjoin(tmp, word, garbage);
	}
	return (1);
}

static int	process_word(char **new_line, t_mini *m_utils, t_gc **garbage)
{
	m_utils->j = m_utils->i;
	while (m_utils->line[m_utils->i] && !ft_chrstr(m_utils->line[m_utils->i],
			"<>") && !ft_whitespaces(m_utils->line[m_utils->i]))
	{
		if (handle_quotes(m_utils->line, &m_utils->i))
			continue ;
		m_utils->i++;
	}
	return (handle_word_concat(new_line, m_utils, garbage));
}

void	ft_minisplit(t_redic **res, t_c *c, t_tk *token, t_mini m_utils)
{
	char	*new_line;

	new_line = NULL;
	*res = NULL;
	while (m_utils.line[m_utils.i])
	{
		skip_spaces_minisplit(m_utils.line, &(m_utils.i));
		if (!m_utils.line[m_utils.i])
			break ;
		if (ft_chrstr(m_utils.line[m_utils.i], "<>"))
		{
			if (!handle_redirection(res, c, m_utils.line, &(m_utils.i)))
				return ;
			continue ;
		}
		if (!process_word(&new_line, &m_utils, c->garbage))
			return ;
	}
	token->token = new_line;
}
