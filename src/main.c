/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:59:26 by akilk             #+#    #+#             */
/*   Updated: 2022/09/12 14:01:38 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

	//ToDo: in parse_ants add error handling for chars etc
	//ToDo: add error if coordinates are wrong?
	// ADD errors if no ##START ##END found
	//ToDo validate links with names
	//ToDo: no single path from start to end

int	error(char **str, char *msg)
{
	if (str)
		ft_strdel(str);
	ft_putendl_fd(msg, 2);
	return (0);
}

int	main(void)
{
	t_farm	farm;
	t_list	*paths;
	int	found_paths;

	parse(&farm);
	print_mtx(&farm);
	printf("BFS starts\n");
	paths = NULL;
	found_paths = find_all_paths(&farm, &paths);
	// print_mtx(&farm);
	// print_paths(&farm, paths, found_paths);
	calculate_routes(&farm, paths, found_paths);
	// run_ants(&farm, paths);
	// free(farm);
	// free(paths);
	return (0);
}
