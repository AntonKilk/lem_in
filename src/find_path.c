/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:02:38 by akilk             #+#    #+#             */
/*   Updated: 2022/09/04 20:23:55 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

/*
** Assign -1 to all rooms' distances(levels)
*/

void	zero_distances(int *result, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		result[i] = -1;
}

/*
** Create array of ints to keep rooms' distances from START.
** Default is -1. Distances are assigned during Breadth First Search (BFS).
*/

int	*new_distances(int size) {
	int *result;

	result = malloc(sizeof(int *) * size);
	if (!result)
		return (NULL);
	zero_distances(result, size);
	return (result);
}

/*
** In next two functions, we move from END to START checking all rooms that
** they are connected to current room and have a distance: current - 1;
** This way we create a path from END to START.
*/

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


/*
** We pack path as structure (t_path) to the list of paths.
*/

void	add2list(t_list **paths, t_list *path, int len)
{
	t_list	*paths_item;
	t_path	*tpath;

	tpath = (t_path *)malloc(sizeof(t_path *));
	tpath->path = path;
	tpath->len = len;
	paths_item = ft_lstnew(tpath, sizeof(*tpath));
	t_path *test = paths_item->content;
	ft_lstadd(paths, paths_item);
}

/*
** After each BFS and DFS (done in function find_path()), we update the
** adjustment matrix that contains links between rooms. We assign 0 to those
** links that are used in found path.
*/

void	update_links(t_farm *farm, int *distances, t_list **paths)
{
	t_list	*path;
	int		fst_room;
	int		snd_room;
	int		len;

	len = 0;
	path = find_path(farm, distances, &len);
	add2list(paths, path, len);
	while (path->next)
	{
		fst_room = * (int *)path->content;
		snd_room = * (int *)path->next->content;
		// printf("1st: %d, 2nd:%d\n", fst_room, snd_room);
		farm->links[fst_room * farm->rooms_nb + snd_room] = 0;
		farm->links[snd_room * farm->rooms_nb + fst_room] = -1;
		path = path->next;
	}
}

/*
** We go with BFS finding distances of rooms from START to END
** then we go back from END to START with DFS finding path and closing
** links of used path as long as there is no paths left between START and END.
** We know that because there won't be distances steps in BFS.
*/

int	find_all_paths(t_farm *farm, t_list **paths)
{
	int	*distances;
	int	found_paths;

	distances = new_distances(farm->rooms_nb);
	found_paths = 0;
	while (bfs(farm, distances))
	{
		update_links(farm, distances, paths);
		zero_distances(distances, farm->rooms_nb);
		found_paths++;
	}
	free(distances);
	return (found_paths);
}
