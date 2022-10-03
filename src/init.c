/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:20:15 by akilk             #+#    #+#             */
/*   Updated: 2022/09/30 19:11:04 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_solution	*init_solution(t_farm *farm)
{
	t_solution	*solution;

	solution = (t_solution *)malloc(sizeof(t_solution));
	if(!solution)
		return (0);
	ft_bzero(solution, sizeof(t_solution));

	farm->start_links = count_links(farm, find_start(farm));
	farm->max_paths = max_paths_nb(farm);
	solution->data = new_int_arr(farm->rooms_nb);
	solution->n_paths = 0;
	solution->starts = new_int_arr(farm->max_paths);
	solution->lengths = new_int_arr(farm->max_paths);
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

t_room	*init_room(t_farm *farm)
{
	t_room	*room;

	room = (t_room *)malloc(sizeof(t_room));
	if(!room)
		return (0);
	ft_bzero(room, sizeof(t_room));
	room->next = -1;
	room->prev = -1;
	room->state = 0;
	return (room);
}
