/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:20:15 by akilk             #+#    #+#             */
/*   Updated: 2022/10/04 14:55:24 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	init_room_info(t_farm *farm, t_room_info *info)
{
	int	i;

	i = 0;
	while (i < farm->rooms_nb)
	{
		info[i].next = -1;
		info[i].prev = -1;
		info[i].state = 0;
		info[i].distance = -1;
		i++;
	}
}

t_solution	*init_solution(t_farm *farm)
{
	t_solution	*solution;
	t_room_info	*room_info;

	solution = (t_solution *)malloc(sizeof(t_solution));
	if(!solution)
		return (0);
	ft_bzero(solution, sizeof(t_solution));

	farm->start_links = count_links(farm, find_start(farm));
	farm->max_paths = max_paths_nb(farm);
	solution->room = (t_room_info *)malloc(sizeof(t_room_info) * farm->rooms_nb);
	if(!solution->room)
		return (0);
	init_room_info(farm, solution->room);
	solution->n_paths = 0;
	solution->starts = new_int_arr(farm->max_paths);
	solution->lengths = new_int_arr(farm->max_paths);
	solution->data = new_int_arr(farm->rooms_nb);
	solution->result = 0;
	return (solution);
}

t_best	*init_best(t_farm *farm)
{
	t_best	*best;

	best = (t_best *)malloc(sizeof(t_best));
	if(!best)
		return (0);
	ft_bzero(best, sizeof(t_best));
	best->solution = new_int_arr(farm->rooms_nb);
	best->starts = new_int_arr(farm->max_paths);
	best->result = 0;
	return (best);
}
