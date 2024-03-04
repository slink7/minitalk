/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_strbuilder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:48:35 by scambier          #+#    #+#             */
/*   Updated: 2024/03/04 18:13:56 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <stdio.h>

#include "libft.h"
#include "t_strbuilder.h"

t_strbuilder	*strbuilder_new(void)
{
	t_strbuilder	*out;

	out = malloc(sizeof(t_strbuilder));
	out->content = ft_calloc(STRBUILDER_SIZE + 1, 1);
	out->index = 0;
	out->next = 0;
	return (out);
}

int	strbuilder_free(t_strbuilder **buffer)
{
	if (!buffer || !*buffer)
		return (0);
	strbuilder_free(&(*buffer)->next);
	free((*buffer)->content);
	free(*buffer);
	*buffer = 0;
	return (1);
}

void	strbuilder_add(t_strbuilder *buffer, char c)
{
	if (buffer->next)
	{
		strbuilder_add(buffer->next, c);
		return ;
	}
	if (buffer->index >= STRBUILDER_SIZE)
	{
		buffer->next = strbuilder_new();
		strbuilder_add(buffer->next, c);
		return ;
	}
	buffer->content[buffer->index++] = c;
}

//void		strbuilder_add(t_strbuilder *buffer, char *str);

int	strbuilder_len(t_strbuilder *buffer)
{
	if (!buffer)
		return (0);
	return (buffer->index + strbuilder_len(buffer->next));
}

char	*strbuilder_get_content(t_strbuilder *buffer)
{
	t_strbuilder	*index;
	int				len;
	char			*out;
	int				out_k;

	len = strbuilder_len(buffer);
	out = malloc(len);
	index = buffer;
	out_k = 0;
	while (index)
	{
		ft_strlcpy(out + out_k, index->content, index->index + 1);
		out_k += index->index;
		index = index->next;
	}
	return (out);
}