/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:41:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/15 16:06:47 by moel-oua         ###   ########.fr       */
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


bool    make_tree(t_tk  *current, t_node **root)
{
    t_node *left = NULL;
    t_node *right = NULL;
    t_node *operator_node = NULL;
    *root= NULL;
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
    // if(*root)
    //     print_tree(*root, 0, 0);
    return true;
}
void create_groups(t_tk **tokens, t_ready **groups, t_gc **garbage) {
    int remaining_tokens = ft_lstsize(*tokens);
    t_tk *current = *tokens;

    while (current && remaining_tokens > 0) {
        char **group = malloc(sizeof(char *) * 4);
        if (!group) {
            fprintf(stderr, "Error: Memory allocation failed for group.\n");
            return;
        }

        group[0] = NULL;
        group[1] = NULL;
        group[2] = NULL;
        group[3] = NULL;

        int priority = current->priority;
        int i = 0;
        if(strcmp( "C", current->op))
        {
            group[0] =  current->token;
            current = current->next;
            i = 3;
            group[1] = NULL;
            remaining_tokens--;
        }
        while (i < 3 && current && remaining_tokens > 0 && priority ==current->priority ) {
            group[i] = current->token;
            current = current->next;
            i++;
            remaining_tokens--;
        }
        if( i == 2)
        {
            current = current->prev;
            group[1] = NULL;
            remaining_tokens--;
            i--;

        }
        group[i] = NULL;
        if (i > 0) {
            ft_add_ready(groups, ft_new_ready(group, priority, garbage));
        } else {
            free(group);
        }
    }
}

bool tokenizer(t_gc **garbage, char *line, t_node **root) {
    t_tk *splitted = NULL;
    t_tk *current = NULL;
    t_ready *groups = NULL;
    t_ready *group = NULL;

    (void)garbage;
    ft_split(&splitted, garbage, line, 0, 0);
    if (!splitted) {
        printf("Error: Token splitting failed.\n");
        return false;
    }

    printf("Split tokens:\n");
    current = splitted;
    while (current) {
        printf("%s[%s]%s", KBLU, current->op, KNRM);
        printf("[%d] ", current->priority);
        if (current->token) {
            printf("[%s]\n", current->token);
        } else {
            printf("[NULL]\n");
        }
        current = current->next;
    }

    printf("====[separator]====\n");

    current = splitted;
    make_tree(current->next, root);
    if (ft_lstsize(current) >= 3) {
        create_groups(&splitted, &groups, garbage);
    }
    printf("Generated groups:\n");
    group = groups;
    while (group != NULL) {
        int i = 0;
        printf("<%i>{ ",group->priority);
        while (group->tokens && group->tokens[i]) {
            printf("[%s] ", group->tokens[i]);
            i++;
        }
        printf("}\n");
        group = group->next;
    }
    return true;
}