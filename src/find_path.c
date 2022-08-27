/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:02:38 by akilk             #+#    #+#             */
/*   Updated: 2022/08/27 14:40:19 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	zero_distances(int *result, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		result[i] = -1;
}

int	*new_distances(int size) {
	int *result;

	result = malloc(sizeof(int *) * size);
	if (!result)
		return (NULL); //add error h
	zero_distances(result, size);
	return (result);
}

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

void	found_paths(t_farm *farm, int *distances)
{
	t_list	*path;
	int		room;
	static int	found_paths;

	found_paths++;
	printf("found path %d\n", found_paths);
	path = find_path(farm, distances);
	while (path)
	{
		room = * (int *)path->content;
		printf("%d", room);
		if (path->next != NULL)
			printf("-");
		path = path->next;
	}
	printf("\n");
}

void	update_links(t_farm *farm, int *distances)
{
	t_list	*path;
	int		fst_room;
	int		snd_room;
	int		size;

	found_paths(farm ,distances);
	size = farm->rooms_nb;
	path = find_path(farm, distances);
	while (path->next)
	{
		fst_room = * (int *)path->content;
		snd_room = * (int *)path->next->content;
		// printf("1st: %d, 2nd:%d\n", fst_room, snd_room);
		farm->links[fst_room * size + snd_room] = 0;
		farm->links[snd_room * size + fst_room] = 0;
		path = path->next;
	}
}

void	find_all_paths(t_farm *farm)
{
	int	*distances;
	int	found_paths;

	distances = new_distances(farm->rooms_nb);
	while (bfs(farm, distances))
	{
		update_links(farm, distances);
		zero_distances(distances, farm->rooms_nb);
	}
	free(distances);
}
