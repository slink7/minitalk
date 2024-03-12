/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:31:27 by scambier          #+#    #+#             */
/*   Updated: 2024/03/12 16:11:08 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <bits/sigaction.h>

#include "libft.h"
#include "set_sig.h"

#define STDOUT 1

unsigned char	right_bitshift_wrap(unsigned char v)
{
	return ((v >> 1) | (v << 7));
}

#define HEAD "\e[1;30m\nReceived \e[1;36m%d\e[1;30m bytes :\n\e[m"
#define MSG "\e[1;37m%s\n\e[m"
#define CONF "\e[1;30mSending configrmation to \e[1;36m%d\n\e[m"

void	handle_reception(t_strbuilder **builder, int pid)
{
	char	*temp;

	temp = ft_strbuilder_build(*builder);
	ft_printf_fd(STDOUT, HEAD, ft_strlen(temp));
	ft_printf_fd(STDOUT, MSG, temp);
	ft_printf_fd(STDOUT, CONF, pid);
	ft_strbuilder_free(builder);
	kill(pid, SIGUSR1);
	if (!ft_strncmp(temp, "exit", 5))
	{
		free(temp);
		exit(0);
	}
	free(temp);
}

void	action(int signum, siginfo_t *siginfo, void *prev)
{
	static t_strbuilder		*builder = 0;
	static unsigned char	byte = 0;
	static int				count = 0;

	(void)prev;
	if (!builder)
		builder = ft_strbuilder_new();
	byte = right_bitshift_wrap(byte + (signum - 10) / 2);
	if (kill(siginfo->si_pid, SIGUSR2))
		ft_printf_fd(1, "kill error\n");
	if (++count < 8)
		return ;
	ft_strbuilder_addchar(builder, byte);
	if (!byte)
		handle_reception(&builder, siginfo->si_pid);
	byte = 0;
	count = 0;
}

#define PID "\e[1;30mStarting server with PID:[\e[1;36m%d\e[1;30m]\n"

int	main(void)
{
	static int	signnums[2] = {SIGUSR1, SIGUSR2};

	set_sig(2, signnums, action);
	ft_printf_fd(1, PID, getpid());
	while (1)
		pause();
}
