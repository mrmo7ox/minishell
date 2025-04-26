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

#endif