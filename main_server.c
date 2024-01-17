/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:31:27 by scambier          #+#    #+#             */
/*   Updated: 2024/01/17 21:01:11 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <bits/sigaction.h>
//#include <asm-generic/signal.h>
//#include <asm/signal.h>

#include <stdio.h>

#include "libft.h"
#include "t_rstack.h"
#include "chrono.h"

t_rstack	g_rs;

int	right_bitshift_wrap(unsigned char v)
{
	return ((v >> 1) | (v << 7));
}

int	g_flag = 1;

void	print_interpret(int signum)
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
	if (byte == 0)
	{
		write(1, "\n", 1);
		printf("%ldms\n", get_time_since_last_call());
		g_flag = 1;
	}
	else
		write(1, &byte, 1);
	byte = 0;
	count = 0;
}

void	sig_handler(int signum)
{
	rstack_write(&g_rs, signum);
}

//600us/char
//1666char/sec

//20ms/char
//500char/sec
int	main(int argc, char **argv)
{
	struct sigaction	sa;
	unsigned char		out;
	int					pid;

	init_rs(&g_rs);
	sa.sa_handler = &sig_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	printf("pid : %d\n", pid);
	while (1)
		if (g_rs.read_index < g_rs.write_index)
		{
			if (g_flag) {
				get_time_since_last_call();
				g_flag = 0;
			}
			print_interpret(rstack_read(&g_rs));
		}
}
