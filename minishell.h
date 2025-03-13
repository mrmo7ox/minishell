/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/03/13 19:26:03 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>

typedef struct s_garbage
{
	void	*addr;
	void	*next;
}			t_gc;

typedef struct s_tokenizer
{
	void	*str;
	void	*token;
	void	*next;
	void	*prev;
}			t_tk;

void	tokenizer(char *line);
t_gc	*ft_new_gc_node(void *content);
t_tk	*ft_new_tk_node(void *content, void *token);
void	ft_add_gc(t_gc **head, t_gc *new);
void	ft_add_tk(t_tk **head, t_tk *new);

#endif