/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:32:04 by scambier          #+#    #+#             */
/*   Updated: 2024/01/19 23:14:23 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <bits/sigaction.h>

#include "libft.h"
#include "send.h"
#include "chrono.h"

void	action(int signum, siginfo_t *siginfo, void *prev)
{
	if (signum != SIGUSR1)
		return ;
	ft_putstr_fd("Confirmation received !", 1);
	exit(0);
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_sigaction = &action;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaction(SIGUSR1, &sa, NULL);
	if (argc < 3 || argc > 4)
		return (0);
	get_time_since_last_call();
	pid = ft_atoi(argv[1]);
	send_str(pid, argv[2], 150);
	ft_putnbr_fd(get_time_since_last_call(), 1);
	sleep(10);
}
