#include "../../minishell.h"

void    cmd_env(char **args, t_env **env)
{
    t_env *head;

    head = *env;
    while (head->next)
    {
        printf("%s=\"%s\"\n",head->name, head->value);
        head = head->next;
    }
}

// int main(int ac, char **av, char **env)
// {
//     t_env *ft_env = NULL;

//     env_init(env, &ft_env);
//     cmd_env(av, &ft_env);
// }