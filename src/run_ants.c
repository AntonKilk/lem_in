/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 08:12:56 by akilk             #+#    #+#             */
/*   Updated: 2022/09/03 15:57:45 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int get_room_from_path(t_list *path)
{
	return (*(int *) path->content);
}

t_path *get_path_from_paths(t_list *paths)
{
	return ((t_path *)paths->content);
}

void	get_paths(t_farm *farm, t_list *paths, int found_paths)
{
	int		room;
	t_list	*paths_ptr;
	t_list	*path_ptr;
	t_path	*path;
	char	**flows;
	int		*room_arr;
	int		i;

	room_arr = (int *)malloc(sizeof (*room_arr) * (farm->rooms_nb));
	if (!room_arr)
		return ; // add error func
	ft_memset(farm->links, 0, farm->rooms_nb);
	ft_lstrev(&paths);
	paths_ptr = paths;
	while (paths_ptr)
	{
		path = get_path_from_paths(paths_ptr);
		path_ptr = path->path;
		printf("path length: %d\n", path->len);
		i = 0;
		while (path_ptr)
		{
			room = get_room_from_path(path_ptr);
			printf("r: %s\n", farm->rooms[room]);
			path_ptr = path_ptr->next;
		}
		paths_ptr = paths_ptr->next;
	}
}


void	calculate_routes(t_farm *farm, t_list *paths, int found_paths)
{
	t_path	*path;

	// lengths = get_lengths(paths, found_paths);
	get_paths(farm, paths, found_paths);
	printf("DONE!\n");
	// 1 -> 5 -> 7 -> 3 -> 2 => int[] path = {0, 5, 0, 0, ..., 7, ...}

	// free(lengths);
}

	// while (i < found_paths)
	// {
	// 	printf("l: %d\n", lengths[i]);
	// 	i++;
	// }



// char	**get_pathstr(t_farm *farm, t_path *path, int len)
// {
// 	t_list	*path_ptr;
// 	char	**result;
// 	int		room;
// 	int		i;

// 	result = (char **)malloc(sizeof (char *) * (len + 1));
// 	if (!result)
// 		return NULL; //add error
// 	result[len] = NULL;
// 	path_ptr = path->path;
// 	i = 0;
// 	while (path_ptr)
// 	{
// 		room = get_room_from_path(path_ptr);
// 		result[i] = ft_strnew(ft_strlen(farm->rooms[room]));
// 		ft_memcpy(result[i], farm->rooms[room], ft_strlen(farm->rooms[room]));
// 		path_ptr = path_ptr->next;
// 		i++;
// 	}
// 	return (result);
// }

// void	print_paths(t_farm *farm, t_list *paths, int found_paths)
// {
// 	int		room;
// 	t_list	*paths_ptr;
// 	t_list	*path_ptr;
// 	t_path	*path;
// 	char	**flows;

// 	printf("found_paths %d\n", found_paths);
// 	ft_lstrev(&paths);
// 	paths_ptr = paths;
// 	while (paths_ptr)
// 	{
// 		path = get_path_from_paths(paths_ptr);
// 		path_ptr = path->path;
// 		printf("path length: %d\n", path->len);
// 		while (path_ptr)
// 		{
// 			room = get_room_from_path(path_ptr);
// 			printf("r: %s\n", farm->rooms[room]);
// 			path_ptr = path_ptr->next;
// 		}
// 		paths_ptr = paths_ptr->next;
// 	}
// }


// int *get_lengths(t_list *paths, int count)
// {
// 	t_path	*path;
// 	int	*lengths;
// 	int	i;

// 	lengths = (int *)malloc(sizeof (int *) * (count));
// 	if (!lengths)
// 		return 0; //add error
// 	i = 0;
// 	ft_lstrev(&paths);
// 	while (i < count)
// 	{
// 		path = get_path_from_paths(paths);
// 		lengths[i] = path->len;
// 		i++;
// 		paths = paths->next;
// 	}
// 	return (lengths);
// }
