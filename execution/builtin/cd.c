/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:36:13 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/23 17:25:12 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *pwd(void)
{
	char *buff;

	buff = getcwd(NULL, 0);
	if (!buff)
		return (NULL);
	// ft_add_gc(gg, ft_new_gc_node(buff));
	// printf("%s\n", buff);
	return (buff);
}

size_t	args_len(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	no_args(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		return ;
	if (chdir(home) == -1)
		ft_putstr_fd("somthing went wrong", 2);
}

void	cd(char **args)
{
	char	*buff;
	char	*tmp;
	size_t	len;

	if (!args)
		return ;
	len = args_len(args);
	if (len == 1)
		no_args();
	else if (len > 2)
		ft_putstr_fd("too many argument\n", 2);
	else if (len == 2)
	{
		buff = pwd();
		tmp = buff;
		buff = ft_strjoin(buff, "/");
		free(tmp);
		tmp = buff;
		buff = ft_strjoin(buff, args[1]);
		free(tmp);
		if (chdir(buff) == -1)
			ft_putstr_fd("no such directory found\n", 2);
	}
}

int main(int ac, char **av)
{
	pid_t pid;

	cd(av);
	char *tmp = pwd();
	printf("%s", tmp);
	free(tmp);
}