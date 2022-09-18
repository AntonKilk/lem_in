/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:34:20 by akilk             #+#    #+#             */
/*   Updated: 2022/09/18 18:04:50 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

/*
** Assign -1 to all rooms' distances(levels)
** Used for all_rooms as well.
*/

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

int	*new_int_arr(int size) {
	int *result;

	result = malloc(sizeof(int *) * size);
	if (!result)
		return (NULL);
	zero_arr(result, size);
	return (result);
}

int	not_in_list(int nb, t_list *path)
{
	while (path)
	{
		// printf ("nb current: %d, nb in list:%d\n", nb, * (int *)path->content);
		if (nb == * (int *)path->content)
			return (0);
		path = path->next;
	}
	return (1);
}
