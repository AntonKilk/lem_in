/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:30:39 by akilk             #+#    #+#             */
/*   Updated: 2022/10/04 16:49:37 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	get_next_start(t_solution *solution)
{
	return (solution->starts[solution->n_paths - 1]);
}

void	zero_unused(t_farm *farm, t_solution *solution)
{
	int	i;

	i = 0;
	while (i < farm->rooms_nb)
	{
		if (solution->room[i].state == 1)
		{
			solution->room[i].state = 0;
			if (i != farm->end)
			{
				solution->room[i].distance = -1;
				solution->room[i].prev = -1;
			}
		}
		i++;
	}
}

void	zero_all(t_farm *farm, t_solution *solution)
{
	init_room_info(farm, solution->room);
	zero_arr(solution->data, farm->rooms_nb);
}

void	fill_solution(t_farm *farm, t_solution *solution)
{
	int	current;

	current = farm->start;
	while(current != farm->end)
	{
		solution->data[current] = solution->room[current].next;
		current = solution->data[current];
	}
}

int	solve(t_farm *farm)
{
	int			start;
	t_solution	*solution;
	t_best		*best;

	best = init_best(farm);
	if(!best)
		return (error(NULL, "Allocation error in solve()\n"));
	solution = init_solution(farm);
	if(!solution)
		return (error(NULL, "Allocation error in solve()\n"));

	// for (size_t i = 0; i < 4; i++)
	while (bfs(farm, solution))
	{
		// if(!bfs(farm, solution))
		// 	break ;
		// printf("states before trackback\n");
		// for (size_t i = 0; i < farm->rooms_nb; i++)
		// {
		// 	printf("%5d", solution->room[i].state);
		// }
		printf("\n");
		if (!track_back(farm, solution))
			zero_all(farm, solution);
		else
		{
			zero_unused(farm, solution);
			fill_solution(farm, solution);
			// calculate_result(farm, solution);
		}


		for (size_t i = 0; i < farm->rooms_nb; i++)
		{
			printf("%5s",farm->rooms[i]);
		}
		printf("\n");
		for (size_t i = 0; i < farm->rooms_nb; i++)
		{
			printf("%5d", solution->room[i].prev);
		}
		printf("\n");
		for (size_t i = 0; i < farm->rooms_nb; i++)
		{
			printf("%5d", solution->room[i].next);
		}
		printf("\n");
		for (size_t i = 0; i < farm->rooms_nb; i++)
		{
			printf("%5d", solution->room[i].state);
		}
		printf("\n");
		for (size_t i = 0; i < farm->rooms_nb; i++)
		{
			printf("%5d", solution->room[i].distance);
		}
		printf("\n solution \n");
		for (size_t i = 0; i < farm->rooms_nb; i++)
		{
			printf("%5d", solution->data[i]);
		}
		printf("\n");
	}
	// print_path(farm, solution, best);
	free_solution(solution, best);
	return (1);
}
