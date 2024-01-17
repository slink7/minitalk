/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:32:04 by scambier          #+#    #+#             */
/*   Updated: 2024/01/18 00:07:01 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "send.h"
#include "chrono.h"

int	main(int argc, char **argv)
{
	int	pid;

	if (argc < 3 || argc > 4)
		return (0);
	get_time_since_last_call();
	pid = ft_atoi(argv[1]);
	send_str(pid, argv[2], ft_atoi(argv[3]));
	ft_putnbr_fd(get_time_since_last_call(), 1);
}
