/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:36:48 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/31 12:28:36 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_retypes	special_cases_redic(char *str)
{
	if (str && ft_strstr(str, "<<"))
		return (HEREDOC);
	else if (str && ft_strstr(str, ">>"))
		return (APPEND);
	else if (str && ft_strstr(str, "<"))
		return (IN);
	else if (str && ft_strstr(str, ">"))
		return (OUT);
	return (CMD);
}

void	skip_spaces_minisplit(char *line, int *i)
{
	while (line[*i] && ft_chrstr(line[*i], " \t"))
		(*i)++;
}

char	*extract_redir(char *line, int *i, int j, t_gc **garbage)
{
	while (line[*i] && ft_chrstr(line[*i], "<>"))
		(*i)++;
	return (ft_copy(&line[j], *i - j, garbage));
}

char	*extract_file(char *line, int *i, int *j, t_c *c)
{
	char	qoute;

	skip_spaces_minisplit(line, i);
	*j = *i;
	while (line[*i] && !ft_chrstr(line[*i], " \t<>"))
	{
		if (ft_chrstr(line[*i], "\"'"))
		{
			qoute = line[*i];
			(*i)++;
			while (qoute != line[*i])
				(*i)++;
			if (qoute == line[*i])
				(*i)++;
			continue ;
		}
		(*i)++;
	}
	return (ft_copy(&line[*j], *i - *j, c->garbage));
}

int	handle_redirection(t_redic **res, t_c *c, char *line, int *i)
{
	int		j;
	char	*redir;
	char	*file;
	char	*combined;
	char	*temp;

	j = *i;
	redir = extract_redir(line, i, j, c->garbage);
	if (!redir)
		return (0);
	file = extract_file(line, i, &j, c);
	if (!file)
		return (free(redir), 0);
	temp = ft_strjoin(redir, " ", c->garbage);
	combined = ft_strjoin(temp, file, c->garbage);
	ft_add_redic(res, ft_new_redic_node(c->garbage, combined));
	return (1);
}
