/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mtx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:51:29 by akilk             #+#    #+#             */
/*   Updated: 2022/09/26 07:19:29 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

/* PRINTS MATRIX OF LINKS,
	where room[i] connected to room[j] if links[i][j] == 1 */
void	print_mtx(t_farm *farm)
{
	int	size;

	size = farm->rooms_nb;
	printf("print matrix with size: %d\n", size);
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


void	print_path(t_farm *farm, t_solution *solution, t_best	*best)
{
	int	i;
	int k;

	printf("end: %d\n", farm->end);
	k = 0;
	while(k < farm->max_paths)
	{
		if (best->starts[k] <= 0)
			return ;
		printf("%s-", farm->start_name);
		i = best->starts[k];
		while(best->solution[i] != farm->end)
		{
			if (best->solution[i] == -1) // for debug
			{
				printf("i:%d, data:%d\n", i, best->solution[i]);
				exit(1);
			}
			printf("%s-", farm->rooms[i]);
			i = best->solution[i];
		}
		printf("%s-%s\n", farm->rooms[i], farm->rooms[best->solution[i]]);
		k++;
	}

}
