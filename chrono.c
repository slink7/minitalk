/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrono.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:25:01 by scambier          #+#    #+#             */
/*   Updated: 2024/01/19 16:15:33 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 199309L
#include <time.h>

#include <stdio.h>

#include "chrono.h"

/*
 1 ns = 0.001 us, 0.000001 ms
 1e9	1e6		1e3
*/

void	ft_nsleep(int ns)
{
	struct timespec	start;
	struct timespec	now;

	clock_gettime(CLOCK_REALTIME, &start);
	while (1)
	{
		clock_gettime(CLOCK_REALTIME, &now);
		if ((now.tv_sec - start.tv_sec) * 1e9
			+ (now.tv_nsec - start.tv_nsec) > ns)
			return ;
	}
}

long	get_time_diff(struct timespec a, struct timespec b, int in_a_sec)
{
	return ((a.tv_sec - b.tv_sec) * in_a_sec
		+ (a.tv_nsec - b.tv_nsec) / (1e9 / in_a_sec));
}

long	get_time_since_last_call(void)
{
	static struct timespec	last = {0, 0};
	struct timespec			now;
	long					out;

	out = -1;
	clock_gettime(CLOCK_REALTIME, &now);
	if (last.tv_sec != 0 || last.tv_nsec != 0)
		out = get_time_diff(now, last, 1e3);
	last = now;
	return (out);
}
