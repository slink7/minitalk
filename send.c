/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:23:36 by scambier          #+#    #+#             */
/*   Updated: 2024/01/16 18:50:08 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

#include "send.h"

int	send_signum(int pid, int signum)
{
	usleep(SEND_COOLDOWN);
	return (kill(pid, signum));
}

int	send_bit(int pid, int bit)
{
	send_signum(pid, 2 * bit + 10);
}

void	send_char(int pid, unsigned char c)
{
	int	k;

	k = -1;
	while (++k < 8)
	{
		send_bit(pid, (c % 2));
		c = c >> 1;
	}
}

void	send_str(int pid, char *str)
{
	while (*str)
		send_char(pid, (unsigned char)*str++);
	send_char(pid, 0);
}