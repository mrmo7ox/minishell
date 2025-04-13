/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:41:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/13 11:53:18 by moel-oua         ###   ########.fr       */
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
    print_indentation(depth);
    if (depth > 0)
    {
        if (is_left)
            printf("├── ");
        else
            printf("└── ");
    }

    printf("%s\n", node->content);

    if (node->left || node->right) 
    {
        print_tree(node->left, depth + 1, 1);  
        print_tree(node->right, depth + 1, 0);
    }
}


bool tokenizer(t_gc **garbage, t_tk **tokens, char *line)
{
    char **splited;
    int i;
    t_node *main = NULL; 
    t_node *left = NULL; 
    t_node *right = NULL; 
	t_node *operator_node;

    (void)garbage;
    (void)tokens;

    if (!line)
        return false;

    splited = ft_split(line, 0, 0);
    if (!splited)
        return false;

    printf("Split tokens:\n");
    for (int j = 0; splited[j]; j++)
    {
        printf("[%d]: %s\n", j, splited[j]);
    }

    for (i = 1; splited[i] != NULL; i += 2) 
    {
        if (splited[i + 1] == NULL)
        {
            printf(" Missing %s\n", splited[i]);
            break;
        }
        operator_node = ft_newtree(splited[i]);
        if (!operator_node)
            return false;

		if (main == NULL)
			left = ft_newtree(splited[i - 1]);
		else 
        	left = main;

        right = ft_newtree(splited[i + 1]);

        if (!left || !right)
        {
            printf("bad left or right \n");
            return false;
        }

        ft_addtree_node(&operator_node, left, right);

        main = operator_node;
    }
	printf("====[separator]====\n");
    if (main)
        print_tree(main, 0, 0);
    return true;
}