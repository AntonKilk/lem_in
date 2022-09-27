/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:57:18 by akilk             #+#    #+#             */
/*   Updated: 2022/09/27 12:29:13 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	preprocess_farm(t_farm *farm)
{
	int	current;
	int	links;
	int	linked[2];
	int	found;
	int	next;
	int removed = 0; // for counting removed

	current = farm->start + 1;
	while (current < farm->rooms_nb)
	{
		if (current == farm->end || current == farm->start)
		{
			current++;
			continue ;
		}
		linked[0] = -1;
		linked[1] = -1;
		found = 0;
		next = 0;
		while (next < farm->rooms_nb)
		{
			if (connected(farm, current, next))
			{
				if (found >= 2)
					break ;
				// printf("проходим:%s-%s\n", farm->rooms[current],farm->rooms[next]);
				linked[found++] = next;
				// if (linked[0] == -1)
				// {
				// 	linked[0] = next;
				// 	found++;
				// }
				// else if (linked[1] == -1)
				// {
				// 	linked[1] = next;
				// 	found++;
				// }
			}
			next++;
		}
		if (found == 1)
		{
			// printf("убрать:%s и %s\n", farm->rooms[current], farm->rooms[linked[0]]);
			farm->links[current * farm->rooms_nb + linked[0]] = 0;
			farm->links[linked[0] * farm->rooms_nb + current] = 0;
			removed++;
			if (linked[0] < current)
				current = linked[0] - 1;
		}
		current++;
	}
	printf("removed:%d\n", removed);
	return (0);
}
