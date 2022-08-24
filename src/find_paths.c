/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:24:25 by akilk             #+#    #+#             */
/*   Updated: 2022/08/24 19:29:04 by akilk            ###   ########.fr       */
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
typedef struct queue
{
	int	head;
	int	tail;
	int	data[0];
} t_queue;

t_queue *new_queue(int size) {
	t_queue *result;

	result = malloc(sizeof(t_queue) + sizeof(int) * size);
	if (!result)
		return (NULL); //add error h
	result->head = 0;
	result->tail = 0;
	return (result);
}

void	put(t_queue *q, int item)
{
	q->data[q->tail++] = item;
}

int	get(t_queue *q)
{
	return (q->data[q->head++]);
}

int	is_empty(t_queue *q)
{
	return (q->head >= q->tail);
}

void	release_queue(t_queue *q)
{
	free (q);
}

void	bfs(t_farm *farm)
{
	t_queue *q;
	t_room	*current;
	int	i;
	int	row;

	q = new_queue(farm->rooms_nb);
	i = 0;
	row = farm->rooms_nb * current->room_nb;
	i += row;
	while (i < farm->rooms_nb)
	{
		put(q, i);
		i++;
	}
	while (!is_empty(q))
		printf("%d\n", get(q));
	release_queue(q);
}
