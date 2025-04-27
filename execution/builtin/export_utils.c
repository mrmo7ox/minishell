#include "../../minishell.h"

static  char    *helper(char *name)
{
    char    *new;
    int     len;
    int     i;

    len = ft_strlen(name);
    i = 0;
    new = (char *)malloc(len * sizeof(char));
    while (i < len - 1)
    {
        new[i] = name[i];
        i++;
    }
    free(name);
    return (new);
}

void    export_append(char *name, char *value, t_env **ft_env)
{
    char *tmp;
    t_env *head;

    name =  helper(name);
    head = *ft_env;
    while (head && strcmp(name, head->name))
        head = head->next;
    if (head)
    {
        tmp = head->value;
        head->value = ft_strjoin(head->value, value);
        free(tmp);
    }
    else 
        ft_putenv(name, value, ft_env);
}

void    ft_upenv(char *name, char *value, t_env **ft_env)
{
    char    *tmp;
    t_env   *head;

    head = *ft_env;
    while (head && strcmp(name, head->name))
        head = head->next;
    if (head)
    {
        tmp = head->value;
        head->value = value;
        free(tmp);
    }
}