/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:23:36 by scambier          #+#    #+#             */
/*   Updated: 2024/01/18 00:53:01 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <time.h>

#include "send.h"
#include "chrono.h"

void send_signum(int pid, int signum)
{
	kill(pid, signum);
}

void send_bit(int pid, int bit)
{
	send_signum(pid, 2 * bit + 10);
}

void	send_char(int pid, unsigned char c, int bit_cooldown)
{
	struct timespec	ms = {0, bit_cooldown};
	int	k;

	k = -1;
	while (++k < 8)
	{
		send_bit(pid, (c % 2));
		usleep(bit_cooldown);
		c = c >> 1;
	}
}

void	send_str(int pid, char *str, int bit_cooldown)
{
	while (*str)
		send_char(pid, (unsigned char)*str++, bit_cooldown);
	send_char(pid, 0, bit_cooldown);
}