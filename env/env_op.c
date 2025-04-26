#include "env.h"

void    env_init(char **env, t_env **ft_env)
{
    int i;
    char **tmp;

    i = 0;
    while(env[i])
    {
        tmp=ft_minisplit(env[i], '=', 0, 0);
        if (!tmp)
            return ;
        ft_add_env(ft_env, ft_new_env(tmp[0], tmp[1]));
        free(tmp);
        i++;
    }
}

void    ft_putenv(char *name, char *value, t_env **ft_env)
{
    ft_add_env(ft_env, ft_new_env(name, value));
}

char    *ft_getenv(char *name, t_env **ft_env)
{
    t_env *head;

    head = *ft_env;
    while (name != head->name)
        head = head->next;
    return (head->value);
}
