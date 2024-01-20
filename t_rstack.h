/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_rstack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:45:15 by scambier          #+#    #+#             */
/*   Updated: 2024/01/19 19:47:02 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_RSTACK_H
# define T_RSTACK_H

# define RSTACK_BUFFER_LEN 32768

typedef struct s_rstack
{
	int	content[RSTACK_BUFFER_LEN];
	int	read_index;
	int	write_index;
}	t_rstack;

void	init_rs(t_rstack *rs);
void	rstack_write(t_rstack *rs, int k);
int		rstack_read(t_rstack *rs);

#endif