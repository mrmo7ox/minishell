/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:56:02 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/31 13:27:51 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*helper(t_c *c, int fd)
{
	char	*str;
	char	*buff;

	str = NULL;
	buff = ft_malloc((2 * sizeof(char)), c->garbage);
	if (read(fd, buff, 1) == -1)
	{
		perror("ft_getpid");
		return (NULL);
	}
	buff[1] = '\0';
	while (buff[0] != ' ')
	{
		str = ft_strjoin(str, buff, c->garbage);
		if (read(fd, buff, 1) == -1)
		{
			perror("ft_getpid");
			return (NULL);
		}
		buff[1] = '\0';
	}
	close(fd);
	return (str);
}

char	*get_pid_str(t_c *c)
{
	int		fd;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
	{
		perror("ft_getpid");
		return (NULL);
	}
	return (helper(c, fd));
}
