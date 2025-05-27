/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:50:13 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/27 13:27:04 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_status(int new_status, int flag)
{
	static int	status;

	if (flag == -1)
	{
		status = new_status;
	}
	return (status);
}

void	handler(int sig)
{
	if (g_signal == SIGINT)
	{
		(void)sig;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		set_status(130, -1);
	}
	else if(g_signal == 69)
	{
		close(0);
		g_signal = 169;
	}
}