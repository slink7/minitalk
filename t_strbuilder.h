/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_strbuilder.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:48:45 by scambier          #+#    #+#             */
/*   Updated: 2024/03/04 20:33:56 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_STRBUILDER_H
# define T_STRBUILDER_H

# define STRBUILDER_SIZE 4

typedef struct s_strbuilder	t_strbuilder;

typedef struct s_strbuilder {
	t_strbuilder	*next;
	char			*content;
	int				index;
}	t_strbuilder;

t_strbuilder	*strbuilder_new(void);
int				strbuilder_free(t_strbuilder **buffer);
void			strbuilder_add(t_strbuilder *buffer, char c);
char			*strbuilder_build(t_strbuilder *buffer);

#endif