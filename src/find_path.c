/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:02:38 by akilk             #+#    #+#             */
/*   Updated: 2022/08/30 07:49:40 by akilk            ###   ########.fr       */
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

int	check_connections(t_farm *farm, t_list **path, int *distances, int current)
{
	int	i;
	int	row;
	t_list	*neighboor;

	row = farm->rooms_nb * (current);
	i = 0;
	while ((i + row) < (farm->rooms_nb + row))
	{
		// printf("r1: %d d: %d, r2: %d d: %d\n", i, distances[i], current, distances[current]);
		if (is_connected(farm, i, row) && distances[i] == distances[current] - 1)
		{
			// printf("HERE\n");
			neighboor = ft_lstnew(&i, sizeof(i));
			ft_lstadd(path, neighboor);
			return (distances[i]) ;
		}
		i++;
	}
	return (0);
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
		if (!check_connections(farm, &path, distances, current))
			break ;
	}
	return (path);
}

/* This runs find path 2nd time */
void	found_paths(t_list *path)
{
	int			room;
	static int	found_paths;

	found_paths++;
	printf("found path %d\n", found_paths);
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

void	add2list(t_list **paths, t_list *path)
{
	t_list	*fst_path;

	fst_path = ft_lstnew(&path, sizeof(t_list *));
	ft_lstadd(paths, fst_path);
}

void	update_links(t_farm *farm, int *distances, t_list **paths)
{
	t_list	*path;
	int		fst_room;
	int		snd_room;
	int		size;

	path = NULL;
	size = farm->rooms_nb;
	path = find_path(farm, distances);
	found_paths(path);
	add2list(paths, path);
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

void	find_all_paths(t_farm *farm, t_list **paths)
{
	int	*distances;
	int	found_paths;

	distances = new_distances(farm->rooms_nb);
	while (bfs(farm, distances))
	{
		update_links(farm, distances, paths);
		zero_distances(distances, farm->rooms_nb);
	}
	free(distances);
}
