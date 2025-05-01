/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/29 15:43:55 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	printf_garbage(t_gc *garbage)
{
	int	i;

	i = 0;
	if (!garbage)
		printf("there's no garbage to clean! expet the dev\n");
	while (garbage)
	{
		i++;
		garbage = garbage->next;
	}
	if (i)
		printf("there's %d addr in the garbage!\n", i);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_gc	*garbage;
	t_env	*ft_env;

	// char	**tmp;
	(void)ac;
	(void)av;
	garbage = NULL;
	ft_env = NULL;
	env_init(env, &ft_env, &garbage);
	load_history();
	while (true)
	{
		line = readline("Minishell: ");
		line = formating(line, &garbage);
		if (!line)
			exit(0);
		add_history(line);
		save_history();
		if (syntax_error(line))
		{
			tokenizer(&garbage, line);
		}
		// tmp = ft_split_test(line, ' ');
		// if (!ft_strcmp(tmp[0], "export"))
		// 	export(tmp, &ft_env, &garbage);
		// else if (!ft_strcmp(tmp[0], "cd"))
		// 	cd(tmp, &garbage);
		// else if (!ft_strcmp(tmp[0], "echo"))
		// 	echo(tmp);
		// else if (!ft_strcmp(tmp[0], "pwd"))
		// 	ft_pwd(tmp, &garbage);
		printf_garbage(garbage);
		free(line);
	}
	return (0);
}
