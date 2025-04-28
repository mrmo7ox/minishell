/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:57:06 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/28 11:44:15 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../minishell.h"
# include "../../env/env.h"


void	cd(char **args);
void	echo(int ac, char **av);
void	cmd_env(char **args, t_env **env);
void	export(char **args, t_env **ft_env);
void	export_append(char *name, char *value, t_env **ft_env);
void	ft_upenv(char *name, char *value, t_env **ft_env);
void	ext_export(char *name, char *value, t_env **ft_env, char **tmp);
void	export_sort(t_env **ft_env);
// char	*pwd(t_gc **gc);

#endif