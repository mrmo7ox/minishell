/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:57:06 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/26 14:22:54 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../minishell.h"
# include "../../env/env.h"


void	cd(char **args);
void	echo(int ac, char **av);
void    cmd_env(char **args, t_env **env);
void	export(char **args, t_env **ft_env);
// char	*pwd(t_gc **gc);

#endif