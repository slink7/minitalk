/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:31:27 by scambier          #+#    #+#             */
/*   Updated: 2024/03/07 13:27:07 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <bits/sigaction.h>

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
	char					*temp;
	static unsigned char	byte = 0;
	static int				count = 0;

	(void)prev;
	if (!builder)
		builder = strbuilder_new();
	byte = right_bitshift_wrap(byte + (signum - 10) / 2);
	if (kill(siginfo->si_pid, SIGUSR2))
		ft_printf_fd(1, "kill error\n");
	if (++count < 8)
		return ;
	strbuilder_add(builder, byte);
	if (!byte)
	{
		temp = strbuilder_build(builder);
		ft_printf_fd(STDOUT, "%s\nReceived %d bytes\n", temp, ft_strlen(temp));
		free(temp);
		ft_printf_fd(STDOUT, "Confirming to %d\n", siginfo->si_pid);
		strbuilder_free(&builder);
		kill(siginfo->si_pid, SIGUSR1);
	}
	byte = 0;
	count = 0;
}

int	main(void)
{
	static int	signnums[2] = {SIGUSR1, SIGUSR2};

	set_sig(2, signnums, action);
	ft_printf_fd(1, "Starting server with PID:[%d]\n", getpid());
	while (1)
		pause();
}
