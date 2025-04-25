/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:13:35 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/25 21:37:47 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *ft_copy(char *src, int len)
{
    char *dup = malloc(len + 1);
    if (!dup)
        return (NULL);

    for (int i = 0; i < len; i++)
        dup[i] = src[i];

    dup[len] = '\0';
    return (dup);
}

e_redic special_cases_redic(char *str)
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
void ft_minisplit(t_redic **res, t_gc **garbage, t_tk *token, char *line, int i, int j)
{
    char *new_line = NULL;
    *res = NULL;

    while (line[i])
    {
        while (line[i] && ft_chrstr(line[i], " \t"))
            i++;
        if (!line[i])
            break;

        // Check for redirection operator
        if (ft_chrstr(line[i], "<>"))
        {
            j = i;
            while (line[i] && ft_chrstr(line[i], "<>"))
                i++;
            char *redir = ft_copy(&line[j], i - j);
            if (!redir)
                return;

            // Skip space after redirection
            while (line[i] && ft_chrstr(line[i], " \t"))
                i++;

            j = i;
            while (line[i] && !ft_chrstr(line[i], " \t<>"))
                i++;
            char *file = ft_copy(&line[j], i - j);
            if (!file)
                return;

            // Join redir + file into one string, like: ">> filename"
            char *full = ft_strjoin(redir, " ");
            char *combined = ft_strjoin(full, file);
            free(redir);
            free(file);
            free(full);

            ft_add_redic(res, ft_new_redic_node(garbage, combined));
            free(combined);
            continue;
        }

        // Handle normal word
        j = i;
        while (line[i] && !ft_chrstr(line[i], " \t<>"))
            i++;
        char *word = ft_copy(&line[j], i - j);
        if (!word)
            return;

        if (!new_line)
            new_line = ft_strdup(word);
        else
        {
            char *tmp = ft_strjoin(new_line, " ");
            free(new_line);
            new_line = ft_strjoin(tmp, word);
            free(tmp);
        }
        free(word);
    }

    token->token = new_line;
}
