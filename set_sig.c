/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sig.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:28:36 by scambier          #+#    #+#             */
/*   Updated: 2024/03/04 20:30:37 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
//#include <bits/sigaction.h>

void	set_sig(int signumc, int signums[], void (*f)(int, siginfo_t *, void *))
{
	struct sigaction	sa;
	int					k;

	sa.sa_sigaction = f;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	k = -1;
	while (k++ < signumc)
	{
		sigaddset(&sa.sa_mask, signums[k]);
		sigaction(signums[k], &sa, 0);
	}
}
