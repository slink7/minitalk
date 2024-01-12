/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:23:45 by scambier          #+#    #+#             */
/*   Updated: 2024/01/12 16:46:23 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	putcharstkt(char *str)
{
	printf("=\t%s\t=\n", str);
	while (*str)
	{
		printf("[%d](%c)\n", (unsigned char)*str, *str);
		str++;
	}
	printf("[%d]\n", (unsigned char)*str);
}

int	main(int argc, char **argv)
{
	putcharstkt(argv[1]);
	putcharstkt("\U00001CC4");
	putcharstkt("\U0001F600");//0x F0 9F 98 80
	putcharstkt("\U00002588");
	putcharstkt("\U0001F49C");
	return (0);
}
