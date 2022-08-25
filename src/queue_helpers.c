/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:08:11 by akilk             #+#    #+#             */
/*   Updated: 2022/08/25 10:04:11 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

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
