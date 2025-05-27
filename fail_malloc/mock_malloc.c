/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:17:55 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/27 11:17:56 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

void	*malloc(size_t size)
{
	static void *(*real_malloc)(size_t) = NULL;
	if (!real_malloc)
	{
		real_malloc = dlsym(RTLD_NEXT, "malloc");
	}

	printf("Intercepted malloc(%zu)\n", size);
	return (real_malloc(size));
}