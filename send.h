/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:40:54 by scambier          #+#    #+#             */
/*   Updated: 2024/01/17 20:52:46 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEND_H
# define SEND_H

#define SEND_COOLDOWN 5

int	    send_signum(int pid, int signum);
int	    send_bit(int pid, int bit);
void	send_char(int pid, unsigned char c);
void	send_str(int pid, char *str);

#endif