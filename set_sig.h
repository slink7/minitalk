/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sig.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:29:41 by scambier          #+#    #+#             */
/*   Updated: 2024/03/04 20:31:30 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_SIG_H
# define SET_SIG_H

# include <signal.h>

void	set_sig(int sigc, int sigs[], void (*f)(int, siginfo_t *, void *));

#endif