/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:31:27 by scambier          #+#    #+#             */
/*   Updated: 2024/01/11 20:19:57 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <stdio.h>

#include "libft.h"

// typedef void (*sighandler_t)(int);

void	f(int signum)
{
	printf("received %d\n", signum);
}

int	main(int argc, char **argv)
{
	int	pid;

	signal(SIGUSR1, f);
	signal(SIGUSR2, f);
	pid = getpid();
	printf("pid : %d\n", pid);
	pause();
}
