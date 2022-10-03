/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:24:25 by akilk             #+#    #+#             */
/*   Updated: 2022/10/03 11:31:55 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	end_reached(t_farm *farm, int *distances)
{
	if (distances[farm->end] == -1)
		return (0);
	return (1);
}

//this function is used  each step during BFS to set distances for connected rooms + 1 from current room
void	set_distances(t_farm *farm, t_queue *q, int *distances, int current)
{
	int	i;
	int	row;
	int	new_distance;

	new_distance = distances[current] + 1;
	// row = farm->rooms_nb * (*current);
	i = 0;
	while (i < farm->rooms_nb)
	{
		// printf("cur: %d i: %d dist:%d\n", current, i, distances[i]);
		if (connected(farm, current, i) && distances[i] == -1)
		{
			// printf("check link %s-%s\n", farm->rooms[current], farm->rooms[i]);
			distances[i] = new_distance;
			printf("room %s has distance: %d\n",farm->rooms[i], distances[i]);
			// current = i;
			put(q, i);
		}
		i++;
	}
}

int	bfs(t_farm *farm, int *distances, t_room *room)
{
	t_queue	*q;
	int		current;

	// printf("room state %d next %d, prev %d\n", room->state, room->next, room->prev);
	current = farm->start;
	q = new_queue(farm->rooms_nb);
	distances[current] = 0;
	put(q, current);
	while (!is_empty(q))
	{
		current = get(q);
		set_distances(farm, q, distances, current);
	}
	if (!end_reached(farm, distances))
	{
		printf("No connections to finish found\n");
		return (0);
	}
	release_queue(q);
	return (1);
}
