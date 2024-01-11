/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:32:04 by scambier          #+#    #+#             */
/*   Updated: 2024/01/11 18:57:10 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>

#include "libft.h"

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 2)
		return (0);
	pid = ft_atoi(argv[1]);
	kill(pid, SIGUSR1);
	kill(pid, SIGUSR2);
	kill(pid, SIGUSR1);
	kill(pid, SIGUSR2);
	kill(pid, SIGUSR2);
}