/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:50:47 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/26 14:05:08 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../minishell.h"

typedef struct s_env
{
	char	*name;
	char	*value;
	void	*next;
}			t_env;

void	ft_add_env(t_env **head, t_env *new);
t_env	*ft_new_env(char *name, char *value);
void    env_init(char **env, t_env **ft_env);
void    ft_putenv(char *name, char *value, t_env **ft_env);
char    *ft_getenv(char *name, t_env **ft_env);

#endif