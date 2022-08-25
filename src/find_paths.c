/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:24:25 by akilk             #+#    #+#             */
/*   Updated: 2022/08/25 08:51:33 by akilk            ###   ########.fr       */
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

static void	lstadd(t_room **alst, t_room *new)
{
	if (alst == NULL)
		return ;
	new->next = *alst;
	*alst = new;
}

static t_room	*lstnew(int room_nb)
{
	t_room	*ptr;

	ptr = (t_room *)malloc(sizeof(t_room));
	if (!ptr)
		return (NULL);
	ptr->room_nb = room_nb;
	ptr->dist = -1;
	ptr->next = NULL;
	return (ptr);
}

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
	t_room	*current;
	int	i;
	int	row;
	int *distances;
	int	new_distance;

	current = lstnew(find_start(farm));
	q = new_queue(farm->rooms_nb);
	put(q, current->room_nb);
	distances = new_distances(farm->rooms_nb);
	while (!is_empty(q))
	{
		get(q);
		// printf("%d\n", tmp);
		// printf("current room nb:%d\n", current->room_nb);
		new_distance = distances[current->room_nb] + 1;
		printf("new distance: %d\n", new_distance);
		i = 0;
		row = farm->rooms_nb * current->room_nb;
		i += row;
		while (i < farm->rooms_nb)
		{
			printf("i: %d\n",farm->links[i + row]);
			if (farm->links[i + row] == 1 && distances[i] == -1)
			{
				printf("i: %d\n",i);
				distances[i] = new_distance;
				current = lstnew(i);
				put(q, i);
			}
			i++;
		}
	}

	// while (!is_empty(q))
	// 	printf("%d\n", get(q));
	release_queue(q);
}
/*

- положить в список стартовую комнату
- дать ей дистанцию 0
- пока в списке что-то есть:
  - достать из списка
  - взять дистанцию этой комнаты
  - для каждого соседа комнаты:
    - если есть дистанция, то ничего не делать
    - иначе поставить дистанцию +1, положить в конец списка
 */
