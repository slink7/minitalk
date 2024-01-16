/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:31:27 by scambier          #+#    #+#             */
/*   Updated: 2024/01/16 04:03:20 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <bits/sigaction.h>

#include <stdio.h>

#include "libft.h"

#define MAX_SIG_BUFFER 128

typedef struct s_rstack
{
	int	content[MAX_SIG_BUFFER];
	int	read_index;
	int	write_index;
}	t_rstack;

t_rstack	g_rs;

void	rstack_write(t_rstack *rs, int k)
{
	rs->content[rs->write_index++ % MAX_SIG_BUFFER] = k;
}

int	rstack_read(t_rstack *rs)
{
	return (rs->content[rs->read_index++ % MAX_SIG_BUFFER]);
}

int	right_bitshift_wrap(unsigned char v)
{
	return ((v >> 1) | (v << 7));
}

void	interprete(int signum)
{
	static unsigned char	byte = 0;
	static int				count = 0;
	int						bit;

	if (signum != 10 && signum != 12)
		return ;
	bit = (signum - 10) / 2;
	byte = right_bitshift_wrap(byte + bit);
	count++;
	if (count < 8)
		return ;
	if (byte == 0)
		write(1, "\n", 1);
	else
		write(1, &byte, 1);
	byte = 0;
	count = 0;
}

void	init_rs(t_rstack *rs)
{
	int	k;

	k = 0;
	while (k > MAX_SIG_BUFFER)
		rs->content[k] = 0;
	rs->read_index = 0;
	rs->write_index = 0;
}

void	sig_handler(int signum)
{
	rstack_write(&g_rs, signum);
}

//600us/char
//1666char/sec
int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	init_rs(&g_rs);
	sa.sa_handler = &sig_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	printf("pid : %d\n", pid);
	while (1)
		if (g_rs.read_index < g_rs.write_index)
			interprete(rstack_read(&g_rs));
}
