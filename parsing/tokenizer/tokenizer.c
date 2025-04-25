#include "../../minishell.h"

const char *token_type_to_str(e_type type)
{
    switch (type)
    {
    case COMMAND:
        return "COMMAND";
    default:
        return "OPERATOR";
    }
}

// // Recursive function to print the tree structure
// void print_tree(t_leaf *node, int depth, int is_left)
// {
//     if (!node)
//         return;

//     for (int i = 0; i < depth; i++)
//         printf("    ");

//     if (depth > 0)
//         printf("%s── ", is_left ? "┌" : "└");

//     printf("[%s]\n", node->token->token);
//     if (node->infile)
//     {
//         for (int i = 0; i < depth; i++)
//             printf("    ");
//         printf("    [IN][%s]\n", node->infile);
//     }
//     if (node->outfile)
//     {
//         for (int i = 0; i < depth; i++)
//             printf("    ");
//         printf("    [OUT][%s]\n", node->outfile);
//     }
//     if (node->delimiter)
//     {
//         for (int i = 0; i < depth; i++)
//             printf("    ");
//         printf("    [D][%s]\n", node->delimiter);
//     }

//     if (node->left)
//     {
//         for (int i = 0; i < depth; i++)
//             printf("    ");
//         printf("    \n");
//         print_tree(node->left, depth + 1, 1);
//     }

//     if (node->right)
//     {
//         for (int i = 0; i < depth; i++)
//             printf("    ");
//         printf("    \n");
//         print_tree(node->right, depth + 1, 0);
//     }
// }

// // Recursive descent parser for the AST
// t_leaf *make_tree(t_tk *tokens)
// {
//     if (!tokens)
//         return NULL;

//     t_leaf *root = NULL;
//     t_tk *current = tokens;

//     // First pass: handle commands and operators
//     while (current)
//     {
//         if (current->type == CMD)
//         {
//             t_leaf *cmd_leaf = new_leaf(current, COMMAND);
//             if (!root)
//                 root = cmd_leaf;
//             else
//             {
//                 t_leaf *temp = root;
//                 while (temp->right)
//                     temp = temp->right;
//                 temp->right = cmd_leaf;
//             }
//         }
//         else if (current->type == INFILE || current->type == OUTFILE || current->type == APPEND || current->type == HEREDOC)
//         {
//             t_leaf *op_leaf = new_leaf(current, OPERATOR);
//             if (!root)
//                 root = op_leaf;

//             if (root->type == COMMAND)
//             {
//                 if (current->type == OUTFILE)
//                 {
//                     root->infile = current->next->token;
//                     current = current->next;
//                 }
//                 else if (current->type == INFILE)
//                 {
//                     root->outfile = current->next->token;
//                     current = current->next;
//                 }
//                 else if (current->type == HEREDOC)
//                 {
//                     root->infile = "heredoc";
//                     root->delimiter = current->next->token;
//                     current = current->next;
//                 }
//                 else if (current->type == APPEND)
//                 {
//                     root->outfile = current->next->token;
//                     root->append = 1;
//                     current = current->next;
//                 }
//             }
//             else
//             {
//                 t_leaf *op_leaf = new_leaf(current, OPERATOR);
//                 op_leaf->left = root;
//                 root = op_leaf;
//             }
//         }
//         else if (current->type == PIPE || current->type == AND || current->type == OR)
//         {
//             t_leaf *op_leaf = new_leaf(current, OPERATOR);
//             if (!root)
//                 root = op_leaf;
//             else
//             {
//                 op_leaf->left = root;
//                 root = op_leaf;
//             }
//         }

//         current = current->next;
//     }

//     return root;
// }
void adding_redirects(t_tk **head, t_gc **garbage)
{
    t_tk *current;

    if (!head)
        return;
    current = (*head);
    while (current)
    {
        current->redics = NULL;
        if (current->type == COMMAND)
        {
            t_redic *new = NULL;
            ft_minisplit(&new, garbage, current, current->token, 0, 0);
            current->redics = new;
        }
        current = current->next;
    }
}

bool tokenizer(t_gc **garbage, char *line)
{
    t_tk *splitted = NULL;
    (void)garbage;

    ft_split(&splitted, garbage, line, 0, 0);

    int num_tokens = ft_lstsize(splitted);

    if (num_tokens == 0)
    {
        printf("Error: No tokens found.\n");
        return false;
    }
    printf("====[Tree Structure]====\n");

    adding_redirects(&splitted, garbage);

    t_tk *current = splitted;
    while (current)
    {

        printf("[%s]", current->token);
        t_redic *redics = current->redics;
        while (redics)
        {
            printf("{%s}", redics->content);
            redics = redics->next;
        }
        printf("\n");

        current = current->next;
    }
    // t_leaf *root = make_tree(splitted);
    // if (!root)
    // {
    //     printf("Error: Failed to build tree.\n");
    //     return false;
    // }

    // print_tree(root, 0, 0);
    return true;
}