/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:41:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/14 13:03:44 by ihamani          ###   ########.fr       */
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

char *rm_parenthesis(char *line, t_gc **gg)
{
    int start;
    int end;

    start = 0;
    end = ft_strlen(line);
    if (line[start] == '(' && line[end - 1] == ')')
        line = ft_substr(line,start + 1 , (end - 1) - 1, gg);
    printf("[%s>\n", line);
    return (line);
}

void	print_list(t_redr *redr)
{
	if (!redr)
		printf("no redr\n");
	while (redr)
	{
		printf("file_name : %s, type : %s, heredoc: %d\n", redr->file_name, redr->type, redr->here_doc);
		redr = redr->next;
	}
}

bool tokenizer(t_gc **garbage, t_tk **tokens, char *line, t_node **root)
{
    char **splited;
    int i;
    *root = NULL;
    t_node *left = NULL; 
    t_node *right = NULL; 
	t_node *operator_node;
	t_redr	*redr;
	
	(void)tokens;

	if (!line)
		return	false;
	redr = NULL;
	rederction(line, &redr, garbage);
	print_list(redr);

	splited = ft_split(line, 0, 0);
	if (!splited)
		return (false);

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
		operator_node = ft_newtree(ft_split(rm_parenthesis(formating(splited[i], garbage), garbage), 0, 0));
        if (!operator_node)
			return false;

		if ((*root) == NULL)
			left = ft_newtree(ft_split(rm_parenthesis(formating(splited[i - 1], garbage), garbage), 0, 0));
		else 
			left = (*root);

        right = ft_newtree(ft_split(rm_parenthesis(formating(splited[i + 1], garbage), garbage), 0,0));

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