/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrono.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:03:09 by scambier          #+#    #+#             */
/*   Updated: 2024/01/17 20:51:27 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHRONO_H
# define CHRONO_H

# define IN_A_SEC 1e3

long	get_time_diff(struct timespec a, struct timespec b, int in_a_sec);
long	get_time_since_last_call();

#endif