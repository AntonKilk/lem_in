/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:59:26 by akilk             #+#    #+#             */
/*   Updated: 2022/08/31 11:56:45 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

	//ToDo: in parse_ants add error handling for chars etc
	//ToDo: add error if coordinates are wrong?
	// ADD errors if no ##START ##END found
	//ToDo validate links with names
	//ToDo: no single path from start to end

int	main(void)
{
	t_farm	farm;
	t_list	*paths;

	parse(&farm);
	print_mtx(&farm);
	printf("BFS starts\n");
	paths = NULL;
	find_all_paths(&farm, &paths);
	print_mtx(&farm);
	print_paths(&farm, paths);
	// run_ants(&farm, paths);
	// free(farm);
	// free(paths);
	return (0);
}
