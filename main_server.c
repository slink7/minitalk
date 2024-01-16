/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:31:27 by scambier          #+#    #+#             */
/*   Updated: 2024/01/16 02:05:18 by scambier         ###   ########.fr       */
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

void	rstack_write(t_rstack *rs, int k)
{
	rs->content[rs->write_index++ % MAX_SIG_BUFFER] = k;
}

int rstack_read(t_rstack *rs)
{
	return rs->content[rs->read_index++ % MAX_SIG_BUFFER];
}

int	right_bitshift_wrap(unsigned char v)
{
	return ((v >> 1) | (v << 7));
}

t_rstack rs;

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

void	init_rs(t_rstack rs)
{
	int	k;

	k = 0;
	while (k > MAX_SIG_BUFFER)
		rs.content[k] = 0;
	rs.read_index = 0;
	rs.write_index = 0;
}

void	sig_handler(int signum)
{
    rstack_write(&rs, signum);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	init_rs(rs);
	sa.sa_handler = &sig_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	printf("pid : %d\n", pid);
	while (1)
		if (rs.read_index < rs.write_index)
			interprete(rstack_read(&rs));
}
/*
void	handle(int sig)
{
	write(1, "Handled", 7);
	if (sig == SIGUSR1)
		write(1, " USR1\n", 6);
	else if (sig == SIGUSR2)
		write(1, " USR2\n", 6);
}

typedef struct sigaction t_sigaction;

int	main(int argc, char **argv)
{
	printf("%d\n", getpid());
	t_sigaction sa;
	sa.sa_handler = &handle;
	// sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	while (1)
		usleep(10000);
	return (0);
}
*/