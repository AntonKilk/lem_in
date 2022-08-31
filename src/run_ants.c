/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 08:12:56 by akilk             #+#    #+#             */
/*   Updated: 2022/08/31 14:23:41 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

// void	add2arr(t_farm *farm, t_list *path, int size)
// {
// 	t_path	**names;
// 	int		i;

// 	i = 0;
// 	names = (char **)malloc(sizeof (char *) * (size + 1));
// 	ft_bzero(names, size);
// 	if (!names)
// 		return ; // add error
// 	while(path)
// 	{
// 		names[i] = strdup(farm->rooms[*(int *)path->content]);
// 		printf("name:%s\n", names[i]);
// 		path = path->next;
// 		i++;
// 	}
// }

// void	get_names(t_farm *farm, t_list *paths)
// {
// 	char	**names;
// 	t_list	*path_ptr;
// 	t_list	*room_ptr;
// 	int		i;


// 	// names = (char **)malloc(sizeof (char *) * (size + 1));
// 	// path_ptr = paths;
// 	// while (path_ptr)
// 	// {
// 	// 	room_ptr = *(t_list **) path_ptr->content;
// 	// 	while (room_ptr)
// 	// 	{
// 	// 		printf("%s", farm->rooms[*(int *)room_ptr->content]);
// 	// 		room_ptr = room_ptr->next;
// 	// 	}
// 	// 	path_ptr = path_ptr->next;
// 	// }
// }

int get_room_from_path(t_list *path)
{
	return (*(int *) path->content);
}

t_path *get_path_from_paths(t_list *paths)
{
	return ((t_path *)paths->content);
}

void	print_paths(t_farm *farm, t_list *paths)
{
	int		room;
	t_list	*paths_ptr;
	t_list	*path_ptr;
	t_path	*path;

	ft_lstrev(&paths);
	paths_ptr = paths;
	while (paths_ptr)
	{
		path = get_path_from_paths(paths_ptr);
		path_ptr = path->path;
		printf("path length: %d\n", path->len);
		while (path_ptr)
		{
			room = get_room_from_path(path_ptr);
			printf("r: %d\n", room);
			path_ptr = path_ptr->next;
		}
		paths_ptr = paths_ptr->next;
	}
}

// void get_room(t_farm *farm, t_list *paths, int i, char **room)
// {
// 	t_list	*path_ptr;
// 	t_list	*room_ptr;

// 	path_ptr = paths;
// 	while (path_ptr)
// 	{
// 		room_ptr = *(t_list **) path_ptr->content;
// 		while (room_ptr)
// 		{
// 			if (i == *(int *)room_ptr->content)
// 			{
// 				*room = farm->rooms[i];
// 				return ;
// 			}
// 			room_ptr = room_ptr->next;
// 		}
// 		path_ptr = path_ptr->next;
// 	}
// 	return ;
// }

// void	run_ants(t_farm *farm, t_list *paths)
// {
// 	printf("ants nb: %zu\n", farm->ants);
// 	int	i;
// 	int	step;
// 	char	*room;

// 	i = 0;
// 	step = 1;
// 	while (step <= farm->ants)
// 	{
// 		get_room(farm, paths, i, &room);
// 		printf("L%d-%s\n", i, room);
// 		i++;
// 		step++;
// 	}
// }
