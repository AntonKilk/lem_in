/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:02:38 by akilk             #+#    #+#             */
/*   Updated: 2022/08/31 14:22:32 by akilk            ###   ########.fr       */
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

t_list	*find_path(t_farm *farm, int *distances, int *len)
{
	t_list	*curr_room;
	t_list	*path;
	int	current;

	path = NULL;
	current = find_end(farm);
	curr_room = ft_lstnew(&current, sizeof(current));
	ft_lstadd(&path, curr_room);
	(*len)++;
	while(current)
	{
		(*len)++;
		current = * (int *)path->content;
		if (!check_connections(farm, &path, distances, current))
			break ;
	}
	return (path);
}

// void	found_paths(t_list *path)
// {
// 	int			room;
// 	static int	found_paths;

// 	found_paths++;
// 	printf("found path %d\n", found_paths);
// 	while (path)
// 	{
// 		room = * (int *)path->content;
// 		printf("%d", room);
// 		if (path->next != NULL)
// 			printf("-");
// 		path = path->next;
// 	}
// 	printf("\n");
// }

void	add2list(t_list **paths, t_list *path, int len)
{
	t_list	*paths_item;
	t_path	*tpath;

	tpath = (t_path *)malloc(sizeof(t_path *));
	tpath->path = path;
	tpath->len = len;
	paths_item = ft_lstnew(tpath, sizeof(t_path));
	t_path *test = paths_item->content;
	ft_lstadd(paths, paths_item);
}

void	update_links(t_farm *farm, int *distances, t_list **paths)
{
	t_list	*path;
	int		fst_room;
	int		snd_room;
	int		len;
	static int	paths_found;

	len = 0;
	path = find_path(farm, distances, &len);
	add2list(paths, path, len);
	paths_found++;
	while (path->next)
	{
		fst_room = * (int *)path->content;
		snd_room = * (int *)path->next->content;
		// printf("1st: %d, 2nd:%d\n", fst_room, snd_room);
		farm->links[fst_room * farm->rooms_nb + snd_room] = 0;
		farm->links[snd_room * farm->rooms_nb + fst_room] = 0;
		path = path->next;
	}
}

void	find_all_paths(t_farm *farm, t_list **paths)
{
	int	*distances;
	int	found_paths;

	distances = new_distances(farm->rooms_nb);
	int i = 0;
	while (bfs(farm, distances) && i < 5)
	{
		i++;
		update_links(farm, distances, paths);
		zero_distances(distances, farm->rooms_nb);
	}
	free(distances);
}
