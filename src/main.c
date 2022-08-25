/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:59:26 by akilk             #+#    #+#             */
/*   Updated: 2022/08/24 19:39:21 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

	//ToDo: in parse_ants add error handling for chars etc
	//ToDo: add error if coordinates are wrong?
	//ToDo validate links with names
	//ToDo: no single path from start to end

int	main(void)
{
	t_farm	farm;

	parse(&farm);
	print_mtx(&farm);
	printf("BFS starts\n");
	bfs(&farm);
	// print_mtx(&farm);
	return (0);
}
