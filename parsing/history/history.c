/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:36:18 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/16 13:42:12 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



void save_history()
{
    if (append_history(1, HISTORY_FILE) != 0){
        fprintf(stderr, "Failed to save history to file!\n");
    }
}

void load_history()
{
    if (read_history(HISTORY_FILE) != 0) {
        printf("No history file found. Starting fresh.\n");
    }
	stifle_history(MAX_HISTORY_LENGTH);
}
