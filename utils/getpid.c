/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:56:02 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/26 19:56:13 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pid_str(void)
{
	int pipefd[2];
	pid_t pid;
	char buffer[16];
	char *pid_str;
	char *argv[] = {"/bin/sh", "-c", "echo $$", NULL};
	char *envp[] = {NULL};
	ssize_t bytes;

	pid_str = NULL;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (NULL);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve(argv[0], argv, envp);
		perror("execve");
		_exit(1);
	}
	else if (pid > 0)
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		bytes = read(pipefd[0], buffer, sizeof(buffer) - 1);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			pid_str = strdup(buffer);
		}
		close(pipefd[0]);
	}
	else
	{
		perror("fork");
		return (NULL);
	}
	return (pid_str);
}