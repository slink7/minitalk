/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:31:27 by scambier          #+#    #+#             */
/*   Updated: 2024/01/22 14:52:01 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <bits/sigaction.h>

#include <stdio.h>

#include "libft.h"
#include "t_rstack.h"
#include "chrono.h"

#define STDOUT 1

t_rstack	g_rs;

int	right_bitshift_wrap(unsigned char v)
{
	return ((v >> 1) | (v << 7));
}

void	action(int signum, siginfo_t *siginfo, void *prev)
{
	static unsigned char	byte = 0;
	static int				count = 0;
	static int				flag = 1;
	int						bit;

	if (flag)
	{
		get_time_since_last_call();
		flag = 0;
	}
	if (signum != 10 && signum != 12)
		return ;
	bit = (signum - 10) / 2;
	byte = right_bitshift_wrap(byte + bit);
	if (++count < 8)
		return ;
	ft_putchar_fd(byte, STDOUT);
	if (byte == 0)
	{
		ft_putchar_fd('\n', STDOUT);
		ft_putnbr_fd(get_time_since_last_call(), 1);
		ft_putchar_fd('\n', STDOUT);
		printf("Sending confirmation to %d\n", siginfo->si_pid);
		kill(siginfo->si_pid, SIGUSR1);
		flag = 1;
	}
	byte = 0;
	count = 0;
}

//	WSL
//189ms pour 100 octets (4233 bits par sec)
//1888ms pour 1000 octets (4237 bits par sec)
//18807ms pour 10000 octets (4253 bits par sec)

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	char				out[8192];
	int					pid;

	init_rs(&g_rs);
	sa.sa_sigaction = &action;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	printf("__PID:%d\n", pid);
	get_time_since_last_call();
	while (1)
		pause();
}
