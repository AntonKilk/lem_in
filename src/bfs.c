/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:24:25 by akilk             #+#    #+#             */
/*   Updated: 2022/10/04 10:09:54 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	end_reached(t_farm *farm, t_solution *solution)
{
	if (solution->room[farm->end].distance == -1)
		return (0);
	return (1);
}

int	track_back(t_farm *farm, t_solution *solution)
{
	int	current;
	int	prev;

	current = farm->end;
	while(current != farm->start)
	{
		prev = solution->room[current].prev;
		solution->room[prev].next = current;
		current = prev;
		if (current != farm->start)
			solution->room[current].state = 2;
	}
}

int	check_state(t_farm *farm, t_solution *solution, int current, int next)
{
	if (solution->room[current].state == ONLYBACK
		&& solution->room[next].state == USED
		&& solution->room[next].distance\
		== solution->room[current].distance - 1)
	{
		printf("going backwards through old path\n");
		solution->room[next].state = PASS;
		return (OK);
	}
	else if (solution->room[next].state == FREE
		&& solution->room[next].distance == -1
		&& solution->room[current].state != ONLYBACK)
	{
		printf("entering FREE\n");
		solution->room[next].state = VISITED;
		return (OK);
	}
	else if (current != farm->start
		&& solution->room[current].state == VISITED
		&& solution->room[next].state == USED)
	{
		//check if possible to move back
		printf("entering USED\n");
		solution->room[next].state = ONLYBACK;
		return (OK);
	}
	else
		return (0);
}

//this function is used  each step during BFS to set distances for connected rooms + 1 from current room
//set t_room_info→next to next room
//set t_room_info→prev to previous room
//set this_room t_room_info→states to 1
void	check_connections(t_farm *farm, t_queue *q, int current, t_solution *solution)
{
	int	next;
	int	row;
	int	new_distance;
	t_room_state	room_state;

	new_distance = solution->room[current].distance + 1;
	next = 0;
	while (next < farm->rooms_nb)
	{
		// printf("cur: %s next: %s\n", farm->rooms[current], farm->rooms[next]);
		if (connected(farm, current, next) && check_state(farm, solution, current, next))
		{
			printf("check link %s-%s\n", farm->rooms[current], farm->rooms[next]);
			solution->room[next].distance = new_distance;
			solution->room[next].prev = current;
			printf("room %s has distance: %d\n",farm->rooms[next], solution->room[next].distance);
			put(q, next);
		}
		next++;
	}
}

int	bfs(t_farm *farm, t_solution *solution)
{
	t_queue	*q;
	int		current;

	current = farm->start;
	q = new_queue(farm->rooms_nb);
	solution->room[current].distance = 0;
	put(q, current);
	while (!is_empty(q))
	{
		current = get(q);
		check_connections(farm, q, current, solution);
	}
	if (!end_reached(farm, solution))
	{
		printf("No connections to finish found\n");
		return (0);
	}
	release_queue(q);
	return (1);
}
