/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:31:27 by scambier          #+#    #+#             */
/*   Updated: 2024/01/18 19:12:53 by scambier         ###   ########.fr       */
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

int	interpret(int signum, char *out)
{
	static unsigned char	byte = 0;
	static int				count = 0;
	int						bit;

	if (signum != 10 && signum != 12)
		return (0);
	bit = (signum - 10) / 2;
	byte = right_bitshift_wrap(byte + bit);
	if (++count < 8)
		return (0);
	*out = byte;
	byte = 0;
	count = 0;
	return (1);
}

void	action(int signum, siginfo_t *siginfo, void *prev)
{
	static unsigned char	byte = 0;
	static int				count = 0;
	int						bit;

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
	}
	byte = 0;
	count = 0;
}

void	sig_handler(int signum)
{
	rstack_write(&g_rs, signum);
}

//100chars : 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789

//600us/char
//1666char/sec

//20ms/char
//500char/sec
int	main(int argc, char **argv)
{
	struct sigaction	sa;
	char				out[8192];
	int					k;
	int					pid;
	int					flag;

	k = 0;
	init_rs(&g_rs);
	sa.sa_sigaction = &action;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	printf("pid : %d\n", pid);
	flag = 1;
	get_time_since_last_call();
	while (1)
	{
		pause();
	}
}
