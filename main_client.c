/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:32:04 by scambier          #+#    #+#             */
/*   Updated: 2024/03/07 14:18:56 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <bits/sigaction.h>

#include "libft.h"
#include "set_sig.h"

#define MAX_TRY 100

int	g_can_send = MAX_TRY;

void	send_char(int pid, unsigned char c)
{
	int	k;

	k = -1;
	while (++k < 8)
	{
		if (kill(pid, (c % 2) * 2 + 10))
		{
			ft_printf_fd(1, "\e[1;31mInvalid PID\n\e[m");
			exit(0);
		}
		while (g_can_send-- > 0)
			usleep(100);
		if (g_can_send == 0)
		{
			ft_printf_fd(1, "\e[1;31mConnection lost :(\n\e[m");
			exit(0);
		}
		usleep(100);
		g_can_send = MAX_TRY;
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
	(void)siginfo;
	(void)prev;
	if (signum == SIGUSR2)
	{
		g_can_send = -1;
		return ;
	}
	ft_printf_fd(1, "\e[0;32mConfirmation received !\n\e[m");
	exit(0);
}

int	main(int argc, char **argv)
{
	static int	signnums[2] = {SIGUSR1, SIGUSR2};

	if (argc < 3 || argc > 4)
		return (0);
	set_sig(2, signnums, action);
	send_str(ft_atoi(argv[1]), argv[2]);
	sleep(1);
	ft_putstr_fd("\e[1;31mConfirmation not received ! >:(\n\e[m", 1);
}
