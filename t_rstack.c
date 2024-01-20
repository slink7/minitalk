/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_rstack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:49:18 by scambier          #+#    #+#             */
/*   Updated: 2024/01/19 19:43:06 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_rstack.h"

void	init_rs(t_rstack *rs)
{
	int	k;

	k = 0;
	while (k > RSTACK_BUFFER_LEN)
		rs->content[k] = 0;
	rs->read_index = 0;
	rs->write_index = 0;
}

void	rstack_write(t_rstack *rs, int k)
{
	rs->content[rs->write_index++ % RSTACK_BUFFER_LEN] = k;
}

int	rstack_read(t_rstack *rs)
{
	return (rs->content[rs->read_index++ % RSTACK_BUFFER_LEN]);
}
