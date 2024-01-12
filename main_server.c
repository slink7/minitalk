/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:31:27 by scambier          #+#    #+#             */
/*   Updated: 2024/01/12 16:01:35 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

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
	printf("now : %d, %d : ", byte, bit);
	byte = right_bitshift_wrap(byte + bit);
	printf("%d %d\n", bit, byte);
	count++;
	if (count < 8)
		return ;
	// if (byte == 0)
	// 	write(1, "\n", 1);
	// else
	write(1, &byte, 1);
	byte = 0;
	count = 0;
}

int	main(int argc, char **argv)
{
	int	pid;

	signal(SIGUSR1, f);
	signal(SIGUSR2, f);
	pid = getpid();
	printf("pid : %d\n", pid);
	while (1)
		usleep(0);
}
