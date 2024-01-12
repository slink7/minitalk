/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:32:04 by scambier          #+#    #+#             */
/*   Updated: 2024/01/12 14:36:00 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <stdio.h>

#include "libft.h"

int	send_signum(int pid, int signum)
{
	int	out;

	out = kill(pid, signum);
	usleep(1000);
	return (out);
}

void	send_char(int pid, char c)
{
	int	k;

	k = -1;
	printf("%c", c);
	while (++k < 8)
	{
		send_signum(pid, 2 * (c % 2) + 10);
		c = c >> 1;
	}
}

void	send_str(int pid, char *str)
{
	while (*str)
		send_char(pid, *str++);
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
