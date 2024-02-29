/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:32:04 by scambier          #+#    #+#             */
/*   Updated: 2024/02/29 17:37:23 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <bits/sigaction.h>

#include <stdio.h>

#include "libft.h"
#include "set_sig.h"

int g_can_send = 1;

void	send_char(int pid, unsigned char c)
{
	int	k;

	k = -1;
	while (++k < 8)
	{
		if (kill(pid, (c % 2) * 2 + 10))
			printf("kill error\n");
		while (!g_can_send)
			usleep(100);
		usleep(100);
		g_can_send = 0;
		c /= 2;
	}
}

void	send_str(int pid, char *str)
{
	while (*str)
		send_char(pid, (unsigned char)*str++);
	send_char(pid, 0);
}

void	action(int signum, siginfo_t *siginfo, void *prev)
{
	if (signum == SIGUSR2)
	{
		g_can_send = 1;
		return ;
	}
	ft_putstr_fd("Confirmation received !\n", 1);
	exit(0);
}

int	main(int argc, char **argv)
{
	int	signnums[2];
	int	pid;

	if (argc < 3 || argc > 4)
		return (0);
	signnums[0] = SIGUSR1;
	signnums[1] = SIGUSR2;
	set_sig(2, signnums, action);
	pid = ft_atoi(argv[1]);
	send_str(pid, argv[2]);
	sleep(1);
	ft_putstr_fd("Confirmation not received ! >:(\n", 1);
}

