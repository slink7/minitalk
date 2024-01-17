/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:40:54 by scambier          #+#    #+#             */
/*   Updated: 2024/01/18 00:06:00 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEND_H
# define SEND_H

# ifndef SEND_COOLDOWN
#  define SEND_COOLDOWN 10000000
# endif

void    send_signum(int pid, int signum);
void    send_bit(int pid, int bit);
void	send_char(int pid, unsigned char c, int bit_cooldown);
void	send_str(int pid, char *str, int bit_cooldown);

#endif