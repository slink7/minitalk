/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:31:27 by scambier          #+#    #+#             */
/*   Updated: 2024/01/13 15:37:49 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <bits/sigaction.h>

#include <stdio.h>

#include "libft.h"

int	right_bitshift_wrap(unsigned char v)
{
	return ((v >> 1) | (v << 7));
}

void	f(int signum)
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

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	sa.sa_handler = &f;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	printf("pid : %d\n", pid);
	while (1)
		usleep(0);
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