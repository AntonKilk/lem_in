/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:02:38 by akilk             #+#    #+#             */
/*   Updated: 2022/08/26 17:16:09 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	check_distances(t_farm *farm, t_list **path, int *distances, int current)
{
	int	i;
	int	row;
	t_list	*neighboor;

	row = farm->rooms_nb * (current);
	i = 0;
	while ((i + row) < (farm->rooms_nb + row))
	{
		if (is_connected(farm, i, row) && distances[i] == distances[current] - 1)
		{
			neighboor = ft_lstnew(&i, sizeof(i));
			ft_lstadd(path, neighboor);
			break ;
		}
		i++;
	}
	return (1);
}


t_list	*find_path(t_farm *farm, int *distances)
{
	t_list	*curr_room;
	t_list	*path;
	int	current;

	path = NULL;
	current = find_end(farm);
	curr_room = ft_lstnew(&current, sizeof(current));
	ft_lstadd(&path, curr_room);
	while(current)
	{
		current = * (int *)path->content;
		if (!check_distances(farm, &path, distances, current))
			break ;
	}
	return (path);
}

void	create_paths(t_farm *farm, int *distances)
{
	t_list	*path;

	path = find_path(farm, distances);
	while (path)
	{
		printf("%d\n", * (int *)path->content);
		path = path->next;
	}
}
