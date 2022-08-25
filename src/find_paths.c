/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:24:25 by akilk             #+#    #+#             */
/*   Updated: 2022/08/25 10:27:49 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	find_start(t_farm *farm)
{
	size_t	i;

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
	size_t	i;

	i = 0;
	while (i < farm->rooms_nb)
	{
		if(!ft_strcmp(farm->end, farm->rooms[i]))
			break;
		i++;
	}
	return (i);
}

// static void	lstadd(t_room **alst, t_room *new)
// {
// 	if (alst == NULL)
// 		return ;
// 	new->next = *alst;
// 	*alst = new;
// }

// static t_room	*lstnew(int room_nb)
// {
// 	t_room	*ptr;

// 	ptr = (t_room *)malloc(sizeof(t_room));
// 	if (!ptr)
// 		return (NULL);
// 	ptr->room_nb = room_nb;
// 	ptr->dist = -1;
// 	ptr->next = NULL;
// 	return (ptr);
// }

// int	get_room_nb(t_farm *farm, int i)
// {
// 	return (i % farm->rooms_nb);
// }

int	*new_distances(int size) {
	int *result;
	int	i;

	result = malloc(sizeof(int *) * size);
	if (!result)
		return (NULL); //add error h
	i = -1;
	while (++i < size)
		result[i] = -1;
	return (result);
}

void	bfs(t_farm *farm)
{
	t_queue *q;
	int	i;
	int	row;
	int	*distances;
	int	new_distance;
	int	current;

	current = find_start(farm);
	q = new_queue(farm->rooms_nb);
	distances = new_distances(farm->rooms_nb);
	distances[current] = 0;
	put(q, current);
	while (!is_empty(q))
	{
		printf("Cycle starts\n");
		current = get(q);
		new_distance = distances[current] + 1;
		row = farm->rooms_nb * current;
		i = 0;
		while ((i + row) < (farm->rooms_nb + row))
		{
			if (farm->links[i + row] == 1 && distances[i] == -1)
			{
				distances[i] = new_distance;
				printf("room %s has distance: %d\n",farm->rooms[i], distances[i]);
				current = i;
				put(q, i);
			}
			i++;
		}
	}
	release_queue(q);
	free(distances);
}
	// while (!is_empty(q))
	// 	printf("%d\n", get(q));
