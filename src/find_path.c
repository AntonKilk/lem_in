/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:02:38 by akilk             #+#    #+#             */
/*   Updated: 2022/09/07 10:12:54 by akilk            ###   ########.fr       */
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

int	not_in_list(int nb, t_list *path)
{
	while (path)
	{
		printf ("nb current: %d, nb in list:%d\n", nb, * (int *)path->content);
		if (nb == * (int *)path->content)
			return (0);
		path = path->next;
	}
	return (1);
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
		if (is_connected(farm, i, row) && not_in_list(i, *path)) // && distances[i] == distances[current] + 1
		{
			// printf("r1: %d d: %d, r2: %d d: %d\n", i, distances[i], current,distances[current]);
			// printf("current link:%d\n", farm->links[current * farm->rooms_nb + i]);
			farm->links[current * farm->rooms_nb + i] = 0;
			if (current == find_start(farm) || i == find_end(farm))
				farm->links[i * farm->rooms_nb + current] = 0;
			else
				farm->links[i * farm->rooms_nb + current] = -1;

			printf("added to list:%d\n", i);
			neighboor = ft_lstnew(&i, sizeof(i));
			ft_lstadd(path, neighboor);
			return (i) ;
		}
		i++;
	}
	return (0);
}

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

t_list	*find_path(t_farm *farm, int *distances, t_list **paths)
{
	t_list	*curr_room;
	t_list	*path;
	int	current;
	int	end;
	int len;

	len = 0;
	path = NULL;
	current = find_start(farm);
	end = find_end(farm);
	curr_room = ft_lstnew(&current, sizeof(current));
	ft_lstadd(&path, curr_room);
	len++;
	printf("cur: %d, %d\n", current, distances[current]);
	printf("end: %d, %d\n", end, distances[end]);
	int i = 0;
	while(1 && i < farm->rooms_nb)
	{
		i++;
		len++;
		current = * (int *)path->content;
		printf("cur in : %d, %d\n", current, distances[current]);
		if (check_connections(farm, &path, distances, current) == end)
			break ;
	}
	ft_lstrev(&path);

	add2list(paths, path, len);
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
** After each BFS and DFS (done in function find_path()), we update the
** adjustment matrix that contains links between rooms. We assign 0 to those
** links that are used in found path.
*/

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
		find_path(farm, distances, paths);
		zero_distances(distances, farm->rooms_nb);
		found_paths++;
	}
	free(distances);
	return (found_paths);
}


// t_list	*find_path(t_farm *farm, int *distances, int *len)
// {
// 	t_list	*curr_room;
// 	t_list	*path;
// 	int	current;

// 	path = NULL;
// 	current = find_end(farm);
// 	curr_room = ft_lstnew(&current, sizeof(current));
// 	ft_lstadd(&path, curr_room);
// 	(*len)++;
// 	while(current)
// 	{
// 		(*len)++;
// 		current = * (int *)path->content;
// 		if (!check_connections(farm, &path, distances, current))
// 			break ;
// 	}
// 	return (path);
// }
