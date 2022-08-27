/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:59:26 by akilk             #+#    #+#             */
/*   Updated: 2022/08/26 17:14:54 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

	//ToDo: in parse_ants add error handling for chars etc
	//ToDo: add error if coordinates are wrong?
	// ADD errors if no ##START ##END found
	//ToDo validate links with names
	//ToDo: no single path from start to end

int	*new_distances(int size) {
	int *result;
	int	i;

	result = malloc(sizeof(int *) * size);
	if (!result)
		return (NULL); //add error h
	i = -1;
	while (++i < size)
		result[i] = -1;
	return (result);
}

int	main(void)
{
	t_farm	farm;
	int	*distances;

	parse(&farm);
	print_mtx(&farm);
	printf("BFS starts\n");

	distances = new_distances(farm.rooms_nb);
	bfs(&farm, distances);
	create_paths(&farm, distances);
	// print_mtx(&farm);
	free(distances);
	return (0);
}
