/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:50:13 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/31 16:12:25 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_status(int new_status, int flag)
{
	static int	status;

	if (flag == -1)
		status = new_status;
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
	else if (g_signal == 69)
	{
		g_signal = 169;
		set_status(130, -1);
		close(0);
	}
}

void	handle_signal_exe(int status)
{
	if (WTERMSIG(status) == SIGINT)
		set_status(130, -1);
	if (WTERMSIG(status) == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)", 2);
		set_status(131, -1);
	}
	if (WIFSIGNALED(status))
		write(1, "\n", 1);
}

void	handle_signal_pip(int tmp, int status)
{
	if (WTERMSIG(status) == SIGINT || WTERMSIG(tmp) == SIGINT)
	{
		if (WTERMSIG(status) == SIGINT)
			set_status(130, -1);
		write(1, "\n", 1);
	}
	if ((WTERMSIG(status) == SIGQUIT))
	{
		set_status(131, -1);
		ft_putstr_fd("Quit (core dumped)", 2);
		write(1, "\n", 1);
	}
}
