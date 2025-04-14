/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:41:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/14 19:30:43 by moel-oua         ###   ########.fr       */
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
    return (line);
}
bool tokenizer(t_gc **garbage, t_tk **tokens, char *line, t_node **root)
{
    t_tk *splitted = NULL;
    t_tk *current = NULL;
    t_node *left = NULL;
    t_node *right = NULL;
    t_node *operator_node = NULL;

    if (!line)
        return false;

    // Allocate memory for the splitted tokens
    splitted = malloc(sizeof(t_tk));
    if (!splitted)
    {
        printf("Memory allocation failed for splitted.\n");
        return false;
    }

    *root = NULL;

    // Perform token splitting
    ft_split(&splitted, line, 0, 0);
    if (!splitted || !splitted->next) // Ensure splitting was successful
    {
        printf("Token splitting failed or no tokens found.\n");
        free(splitted);
        return false;
    }

    // Traverse the tokens and build the tree
    current = splitted->next; // Skip the head node if it exists
    while (current)
    {
        if (!current->next)
        {
            printf("Error: Missing token after '%s'.\n", current->token);
            break; // Exit the loop as there are no more valid tokens
        }

        operator_node = ft_newtree(current->token); // Create operator node
        if (!operator_node)
        {
            printf("Error: Failed to create operator node.\n");
            return false;
        }

        if (!(*root))
            left = ft_newtree(current->prev->token); // Create left node if root is null
        else
            left = *root; // Use the existing tree as the left subtree

        right = ft_newtree(current->next->token); // Create right node

        if (!left || !right)
        {
            printf("Error: Failed to create left or right node.\n");
            return false;
        }

        ft_addtree_node(&operator_node, left, right); // Add operator node to the tree
        *root = operator_node; // Update the root to the current operator node

        current = current->next->next; // Move to the next operator
    }

    // Print the tree if the root is valid
    if (*root)
        print_tree(*root, 0, 0);

    // Free the splitted tokens if necessary
    // Note: Ensure proper cleanup by freeing memory used for the tokens
    ft_free_tokens(splitted);

    return true;
}