/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mtx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:51:29 by akilk             #+#    #+#             */
/*   Updated: 2022/08/25 08:56:57 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

/* PRINTS MATRIX OF LINKS,
	where room[i] connected to room[j] if links[i][j] == 1 */
void	print_mtx(t_farm *farm)
{
	size_t	size;

	size = farm->rooms_nb;
	printf("print matrix with size: %zu\n", size);
	int i = 0;
	printf("|-> ");
	while (i < size)
		printf("%3.3s", farm->rooms[i++]);
	printf("\n");
	i = 0;
	int k = 0;
	printf("%4.4s", farm->rooms[k++]);
	while(i < size * size)
	{
		printf("%3d", farm->links[i]);
		if (i % size== size - 1)
		{
			printf("\n");
			if (k < size)
				printf("%4.4s", farm->rooms[k++]);
		}
		i++;
	}
	printf("\n");
}
