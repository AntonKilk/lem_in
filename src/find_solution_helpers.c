/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:34:20 by akilk             #+#    #+#             */
/*   Updated: 2022/09/23 11:17:05 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

/*
** Assign -1 to all rooms' distances(levels)
** Used for all_rooms as well.
*/

void	intcpy(int *dest, int *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
}

void	zero_arr(int *result, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		result[i] = -1;
		i++;
	}
}

/*
** Create array of ints to keep rooms' distances from START.
** Default is -1. Distances are assigned during Breadth First Search (BFS).
*/

int	*new_int_arr(int size)
{
	int *result;

	result = (int *)malloc(sizeof(int) * size);
	if (!result)
		return (NULL);
	zero_arr(result, size);
	return (result);
}

int	find_start(t_farm *farm)
{
	int	i;

	i = 0;
	while (i < farm->rooms_nb)
	{
		if(!ft_strcmp(farm->start, farm->rooms[i]))
			break;
		i++;
	}
	return (i);
}

int	find_end(t_farm *farm)
{
	int	i;

	i= 0;
	while (i < farm->rooms_nb)
	{
		if(!ft_strcmp(farm->end, farm->rooms[i]))
			break;
		i++;
	}
	return (i);
}

int	connected(t_farm *farm, int from, int to)
{
	return (farm->links[from * farm->rooms_nb + to]);
}

int	count_links(t_farm *farm, int node)
{
	int *row;
	int	sum;
	int	i;

	i = 0;
	sum = 0;
	row = farm->links + node * farm->rooms_nb;
	while (i < farm->rooms_nb)
	{
		sum += row[i];
		i++;
	}
	return (sum);
}

int	max_paths_nb(t_farm *farm)
{
	int	start = find_start(farm);
	int	end = find_end(farm);

	return (ft_min(count_links(farm, start), count_links(farm, end)));
}

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
	best->result = MAX_INT;
	return (best);
}
