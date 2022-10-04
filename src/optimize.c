/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:57:18 by akilk             #+#    #+#             */
/*   Updated: 2022/10/04 15:15:43 by akilk            ###   ########.fr       */
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
		int move_on = 0;
		while (next < farm->rooms_nb)
		{
			if (connected(farm, current, next))
			{
				if (found >= 2)
				{
					move_on = 1;
					break ;
				}
				linked[found++] = next;
			}
			next++;
		}
		if (found == 1)
		{
			//printf("убрать:%s и %s\n", farm->rooms[current], farm->rooms[linked[0]]);
			farm->links[current * farm->rooms_nb + linked[0]] = 0;
			farm->links[linked[0] * farm->rooms_nb + current] = 0;
			removed++;
			if (linked[0] < current)
				current = linked[0] - 1;
		}
		if (!move_on && found == 2 && !(linked[0] == farm->start
			&& linked[1] == farm->end)
			&& !(linked[1] == farm->end
			&& linked[0] == farm->start))
		{
			// printf("1 убрать связи у %s\n", farm->rooms[current]);
			int l1 = connected(farm, current, linked[0]);
			int l2 = connected(farm, current, linked[1]);
			int ol = connected(farm, linked[0], linked[1]);
			// printf("l1 %d l2 %d ol %d\n", l1, l2, ol);
			set_link(farm, current, linked[0], 0);
			set_link(farm, current, linked[1], 0);
			if ( ol == 0  || (ol > l1 + l2))
				set_link(farm, linked[0], linked[1], l1 + l2);
		}
		current++;
	}
	printf("removed:%d\n", removed);
	return (0);
}
