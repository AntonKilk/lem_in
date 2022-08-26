/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:02:38 by akilk             #+#    #+#             */
/*   Updated: 2022/08/26 11:19:44 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_path *new_path(int room) {
	t_path *path;

	path = malloc(sizeof(t_path));
	if (!path)
		return (NULL); //add error h
	path->room = room;
	path->next = 0;
	return (path);
}

int	find_path(t_farm *farm, int *distances)
{
	t_list	*current;
	t_list	*path;
	int	end;
	/*
	create new list using lstnew, lstadd
	put end to the list
	go to the beginning check if connected and distance -1
	if start found return ok and save path
	 */
	path = NULL;
	end = find_end(farm);
	current = ft_lstnew(&end, sizeof(end));
	//printf("current %d\n", * (int *)current->content);
	ft_lstadd(&path, current);
	while(path)
	{
		path = path->next;
		while ()
	}

	return (1);
}
	// for (int k = 0; k < farm->rooms_nb; k++)
	// 	printf("%d\n", distances[k]);
