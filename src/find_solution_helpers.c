/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:34:20 by akilk             #+#    #+#             */
/*   Updated: 2022/09/28 15:32:07 by akilk            ###   ########.fr       */
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
		if(!ft_strcmp(farm->start_name, farm->rooms[i]))
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
		if(!ft_strcmp(farm->end_name, farm->rooms[i]))
			break;
		i++;
	}
	return (i);
}

int	connected(t_farm *farm, int from, int to)
{
	return (farm->links[from * farm->rooms_nb + to]);
}

void	set_length(t_farm *farm, int from, int to, int len)
{
	farm->links[from * farm->rooms_nb + to] = len;
	farm->links[to * farm->rooms_nb + from] = len;
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
	return (ft_min(count_links(farm, farm->start), count_links(farm, farm->end)));
}
