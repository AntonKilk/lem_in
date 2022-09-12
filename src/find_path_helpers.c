/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:34:20 by akilk             #+#    #+#             */
/*   Updated: 2022/09/12 14:35:54 by akilk            ###   ########.fr       */
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
		// printf ("nb current: %d, nb in list:%d\n", nb, * (int *)path->content);
		if (nb == * (int *)path->content)
			return (0);
		path = path->next;
	}
	return (1);
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