/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:41:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/14 20:14:34 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void print_indentation(int depth)
{
    for (int i = 0; i < depth; i++)
    {
        printf("    "); // 4 spaces per depth level
    }
}

void print_tree(t_node *node, int depth, int is_left)
{
    if (!node)
        return;

    for (int i = 0; i < depth; i++)
        printf("   ");

    if (depth > 0)
        printf("%s── ", is_left ? "┌" : "└");

    printf("[%s]\n", node->content);

    print_tree(node->left, depth + 1, 1);
    print_tree(node->right, depth + 1, 0);
}

bool tokenizer(t_gc **garbage, char *line, t_node **root)
{
    t_tk *splitted = NULL;
    t_tk *current = NULL;
    t_node *left = NULL;
    t_node *right = NULL;
    t_node *operator_node = NULL;
    (void)garbage;

    ft_split(&splitted, garbage,line, 0, 0);
    if (!splitted)
    {
        printf("Error: Token splitting failed.\n");
        return false;
    }

    *root = NULL;
    current = splitted->next;
    while (current)
    {
        if (!current->next)
        {
            printf("Error: Missing token after '%s'.\n", current->token);
            break;
        }

        operator_node = ft_newtree(current->token);
        if (!operator_node)
        {
            printf("Error: Failed to create operator node.\n");
            return false;
        }

        if (!(*root))
            left = ft_newtree(current->prev->token);
        else
            left = *root;

        right = ft_newtree(current->next->token);
        if (!left || !right)
        {
            printf("Error: Failed to create left or right node.\n");
            return false;
        }

        ft_addtree_node(&operator_node, left, right);
        *root = operator_node;

        current = current->next->next;
    }

    if (*root)
        print_tree(*root, 0, 0);

    return true;
}