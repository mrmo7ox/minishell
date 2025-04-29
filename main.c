/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:08 by moel-oua          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/29 10:14:52 by moel-oua         ###   ########.fr       */
=======
/*   Updated: 2025/04/29 11:07:54 by ihamani          ###   ########.fr       */
>>>>>>> f43f88e2ee2c6394af5b17ce82c556eac1cf348f
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

<<<<<<< HEAD
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

int	main(void)
{
	char	*line;
	t_gc	*garbage;

	garbage = NULL;
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
		printf_garbage(garbage);
		free(line);
	}
	return (0);
}
=======
void printf_garbage(t_gc *garbage)
{
	int i = 0;

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

void printf_freed(t_gc *garbage)
{
	int i = 0;

	if (!garbage)
		printf("no garbage found\n");
	while (garbage)
	{
		i++;
		garbage = garbage->next;
	}
	if (i)
		printf("there's still %d leak \n", i);
}

// int main(void)
// {
// 	char	*line;
// 	t_gc	*garbage = NULL;
// 	t_node	*root = NULL;
// 	load_history();
// 	while (true)
// 	{
// 		line = readline("Minishell: ");
// 		if (!line)
// 		{
// 			free_garbage(&garbage);
// 			printf_freed(garbage);
// 			exit(0);
// 		}
// 		if (!strcmp(line, "exit"))
// 		{
// 			free_garbage(&garbage);
// 			printf_freed(garbage);
// 			exit(0);
// 		}
// 		line = formating(line, &garbage);
// 		add_history(line);
// 		save_history();

// 		if (syntax_error(line))
// 		{
// 			tokenizer(&garbage, line , &root);
// 		}
// 		printf_garbage(garbage);
// 		// if()
// 		// {
// 		// 	// ft_add_gc(&garbage, ft_new_gc_node(line));
// 		// 	// tokenizer(&garbage, &tokens, line);
// 		// }
// 	}
// }
int main(int ac, char **av, char **env)
{
	t_env *ft_env = NULL;
	t_gc *gg = NULL;

	env_init(env, &ft_env);
	export(av, &ft_env, &gg);
	no_args(&ft_env);
}

// for testing
// int main(int ac , char **dc)
// {
// 	char	*line;
// 	t_gc	*garbage;
// 	t_tk	*tokens;

// 	if(ac >= 2 )

// 	{
// 		int i = 1;
// 		line = dc[i];
// 		while(dc[i])
// 		{
// 			i++;
// 			line = ft_strjoin(line, dc[i]);
// 		}
// 		printf("[TEST] [%s]\n", line);
// 		ft_add_gc(&garbage, ft_new_gc_node(line));
// 		tokenizer(&garbage, &tokens, line);
// 	}
// }
>>>>>>> f43f88e2ee2c6394af5b17ce82c556eac1cf348f
