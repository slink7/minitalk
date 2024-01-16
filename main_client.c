/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:32:04 by scambier          #+#    #+#             */
/*   Updated: 2024/01/16 02:38:20 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <stdio.h>

#include "libft.h"

#define SEND_COOLDOWN 5

int	send_signum(int pid, int signum)
{
	int	out;

	usleep(SEND_COOLDOWN);
	out = kill(pid, signum);
	return (out);
}

void	send_char(int pid, unsigned char c)
{
	int	k;

	k = -1;
	while (++k < 8)
	{
		send_signum(pid, 2 * (c % 2) + 10);
		c = c >> 1;
	}
}

void	send_str(int pid, char *str)
{
	while (*str)
		send_char(pid, (unsigned char)*str++);
	send_char(pid, 0);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		return (0);
	pid = ft_atoi(argv[1]);
	send_str(pid, argv[2]);
}
