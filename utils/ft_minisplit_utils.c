/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:36:48 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/29 10:58:57 by moel-oua         ###   ########.fr       */
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

char	*extract_file(char *line, int *i, int *j, t_gc **garbage)
{
	skip_spaces_minisplit(line, i);
	*j = *i;
	while (line[*i] && !ft_chrstr(line[*i], " \t<>"))
		(*i)++;
	return (ft_copy(&line[*j], *i - *j, garbage));
}

int	handle_redirection(t_redic **res, t_gc **garbage, char *line, int *i)
{
	int		j;
	char	*redir;
	char	*file;
	char	*combined;
	char	*temp;

	j = *i;
	redir = extract_redir(line, i, j, garbage);
	if (!redir)
		return (0);
	file = extract_file(line, i, &j, garbage);
	if (!file)
		return (free(redir), 0);
	temp = ft_strjoin(redir, " ", garbage);
	combined = ft_strjoin(temp, file, garbage);
	free(redir);
	free(file);
	free(temp);
	ft_add_redic(res, ft_new_redic_node(garbage, combined));
	free(combined);
	return (1);
}
