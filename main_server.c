/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:31:27 by scambier          #+#    #+#             */
/*   Updated: 2024/03/04 18:16:40 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <bits/sigaction.h>

#include <stdio.h>

#include "libft.h"
#include "set_sig.h"
#include "t_strbuilder.h"

#define STDOUT 1

unsigned char	right_bitshift_wrap(unsigned char v)
{
	return ((v >> 1) | (v << 7));
}

void	action(int signum, siginfo_t *siginfo, void *prev)
{
	static t_strbuilder		*builder = 0;
	static unsigned char	byte = 0;
	static int				count = 0;
	int						bit;

	if (signum != 10 && signum != 12)
		return ;
	if (!builder)
		builder = strbuilder_new();
	bit = (signum - 10) / 2;
	byte = right_bitshift_wrap(byte + bit);
	if (kill(siginfo->si_pid, SIGUSR2))
		printf("kill error\n");
	if (++count < 8)
		return ;
	strbuilder_add(builder, byte);
	if (byte == 0)
	{
		ft_putstr_fd(strbuilder_get_content(builder), STDOUT);
		ft_putchar_fd('\n', STDOUT);
		strbuilder_free(&builder);
		printf("Sending confirmation to %d\n", siginfo->si_pid);
		kill(siginfo->si_pid, SIGUSR1);
	}
	byte = 0;
	count = 0;
}

int	main(int argc, char **argv)
{
	int	signnums[2];

	signnums[0] = SIGUSR1;
	signnums[1] = SIGUSR2;
	set_sig(2, signnums, action);
	printf("SERVER:\n\tPID:%d\n", getpid());
	while (1)
		pause();
}
