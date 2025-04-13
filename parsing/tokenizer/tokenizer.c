/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:41:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/13 15:32:04 by moel-oua         ###   ########.fr       */
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

    for (int i = 0; node->content[i] ;  i++)
    {
        printf("[%s]", node->content[i]);
        if(  node->content[i + 1] != NULL)
            printf(" "); 
    }
    printf("\n");    

    if (node->left || node->right) 
    {
        print_tree(node->left, depth + 1, 1);  
        print_tree(node->right, depth + 1, 0);
    }
}

char *rm_parenthesis(char *line)
{
    int start;
    int end;

    start = 0;
    end = ft_strlen(line);
    if (line[start] == '(' && line[end - 1] == ')')
        line = ft_substr(line,start + 1 , (end - 1) - 1);
    printf("[%s>\n", line);
    return (line);
}

bool tokenizer(t_gc **garbage, t_tk **tokens, char *line, t_node **root)
{
    char **splited;
    int i;
    *root = NULL;
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
        operator_node = ft_newtree(ft_split(rm_parenthesis(formating(splited[i])), 0, 0));
        if (!operator_node)
            return false;

		if ((*root) == NULL)
			left = ft_newtree(ft_split(rm_parenthesis(formating(splited[i - 1])), 0, 0));
		else 
        	left = (*root);

        right = ft_newtree(ft_split(rm_parenthesis(formating(splited[i + 1])), 0,0));

        if (!left || !right)
        {
            printf("bad left or right \n");
            return false;
        }

        ft_addtree_node(&operator_node, left, right);

        (*root) = operator_node;
    }
	printf("====[separator]====\n");
    if ((*root))
        print_tree((*root), 0, 0);
    return true;
}