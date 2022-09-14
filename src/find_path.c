/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:02:38 by akilk             #+#    #+#             */
/*   Updated: 2022/09/13 11:30:55 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

/*
** In next two functions, we move from END to START checking all rooms that
** they are connected to current room;
** This way we create a path from END to START.
*/

int	check_connections(t_farm *farm, t_list **path, int *distances, int current)
{
	int	i;
	int	row;
	t_list	*neighboor;

	row = farm->rooms_nb * (current);
	i = 0;
	while ((i + row) < (farm->rooms_nb + row))
	{
		if (is_connected(farm, i, row)) // && distances[i] == distances[current] -1
		{
			// printf("r1: %d d: %d, r2: %d d: %d\n", i, distances[i], current,distances[current]);
			// printf("current link:%d\n", farm->links[current * farm->rooms_nb + i]);
			farm->links[i * farm->rooms_nb + current] = 0;
			// if (current == find_end(farm)) // || i == find_start(farm)
			// 	farm->links[current * farm->rooms_nb + i] = 0;
			// else
			farm->links[current * farm->rooms_nb + i] = -1;

			// printf("added to list:%d\n", i);
			neighboor = ft_lstnew(&i, sizeof(i));
			ft_lstadd(path, neighboor);
			return (i) ;
		}
		i++;
	}
	return (0);
}

void	fill_visited(t_list *path, int *visited)
{
	int	i;

	i = * (int *)path->content;
	while (path->next)
	{
		path = path->next;
		visited[i] = * (int *)path->content;
		printf("visited[%d]: %d\n", i, visited[i]);
		i = visited[i];
	}
}

t_list	*find_path(t_farm *farm, int *distances, t_list **paths, int *visited)
{
	t_list	*curr_room;
	t_list	*path;
	int	current;
	int	end;
	int len;

	len = 0;
	path = NULL;
	current = find_end(farm);
	curr_room = ft_lstnew(&current, sizeof(current));
	ft_lstadd(&path, curr_room);
	len++;
	printf("curr room: %s, %d\n", farm->rooms[current], distances[current]);
	while(current)
	{
		len++;
		current = * (int *)path->content;
		printf("cur in : %s, %d\n", farm->rooms[current], distances[current]);
		if (!check_connections(farm, &path, distances, current))
			break ;
	}
	fill_visited(path, visited);
	add2list(paths, path, len);
	return (path);
}
