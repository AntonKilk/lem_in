/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:30:39 by akilk             #+#    #+#             */
/*   Updated: 2022/09/30 19:24:25 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	get_next_start(t_solution *solution)
{
	return (solution->starts[solution->n_paths - 1]);
}

// int	find_length(t_farm *farm, t_solution *solution)
// {
// 	int	length;
// 	int	i;

// 	i = solution->starts[solution->n_paths - 1];
// 	length = connected(farm, farm->start, i);
// 	// printf("start: %s\n", farm->rooms[i]);
// 	if (solution->data[i] == farm->end)
// 		length += connected(farm, i, solution->data[i]);
// 	while(solution->data[i] != farm->end)
// 	{
// 		if (solution->data[i] == -1)
// 			return (error(NULL, "Wrong data in find_lenght()"));
// 		length += connected(farm, i, solution->data[i]);
// 		i = solution->data[i];
// 	}
// 	// printf("\nLength:%d\n", length);
// 	return (length);
// }

// int	evaluate(t_farm *farm, t_solution *t_solution)
// {
// 	int	ants;
// 	int	d;
// 	int	result;
// 	int	i;
// 	int	p1;
// 	int	p2;
// 	int	moved;
// 	int	*sortedlens;


// 	//Get rid of all negative values in lengths// create a separate func
// 	/* new f */
// 	i = 0;
// 	int	new_len = 0;
// 	while (i < farm->max_paths)
// 	{
// 		if (t_solution->lengths[i] > 0)
// 			new_len++;
// 		i++;
// 	}
// 	sortedlens = new_int_arr(new_len);
// 	i = 0;
// 	int k = 0;
// 	while (i < farm->max_paths)
// 	{
// 		if (t_solution->lengths[i] > 0)
// 			sortedlens[k++] = t_solution->lengths[i];
// 		i++;
// 	}
// 	// intcpy(sortedlens, t_solution->lengths + i, new_len);
// 	// bubble_sort(sortedlens, new_len);
// 	/* new f */

// 	// calculate
// 	result = sortedlens[0];
// 	d = 1;
// 	ants = farm->ants;
// 	i = 0;
// 	while (i + 1 < new_len)
// 	{
// 		p1 = sortedlens[i];
// 		p2 = sortedlens[i + 1];
// 		moved = (p2 - p1) * d;
// 		if (ants <= moved)
// 			break ;
// 		ants -= moved;
// 		result += p2 - p1;
// 		d += 1;
// 		i++;
// 	}
// 	result += ants / d;
// 	if (ants % d)
// 		result += 1;
// 	// printf("result in evaluate: %d\n", result);
// 	free(sortedlens);
// 	return (result);
// }

// void	fill_lengths(int length, t_farm *farm, t_solution *solution)
// {
// 	int	i;
// 	solution->lengths[solution->n_paths - 1] = length;
// 	// zero lengths if no starts
// 	i = 0;
// 	while (i < farm->max_paths)
// 	{
// 		if (solution->starts[i] == -1)
// 			solution->lengths[i] = -1;
// 		i++;
// 	}
// }

// void	fill_best(t_farm *farm, t_solution *solution, t_best *best)
// {
// 	if (solution->result != 0 && best->result == 0)
// 	{
// 		best->result = solution->result;
// 		intcpy(best->solution, solution->data, farm->rooms_nb);
// 		intcpy(best->starts, solution->starts, farm->max_paths);
// 	}
// 	else if (solution->result < best->result)
// 	{
// 		best->result = solution->result;
// 		intcpy(best->solution, solution->data, farm->rooms_nb);
// 		intcpy(best->starts, solution->starts, farm->max_paths);
// 	}
// }


int	solve(t_farm *farm, int *distances)
{
	int			start;
	t_solution	*solution;
	t_best		*best;
	t_room		*room;

	best = init_best(farm);
	if(!best)
		return (error(NULL, "Allocation error in solve()\n"));
	solution = init_solution(farm);
	if(!solution)
		return (error(NULL, "Allocation error in solve()\n"));
	room = init_room(farm);
	if(!room)
		return (error(NULL, "Allocation error in solve()\n"));


	// pass room to bfs
	// fill room state, prev during bfs
	bfs(farm, distances, room);

	// print_path(farm, solution, best);
	free_solution(solution, best);
	return (1);
}
