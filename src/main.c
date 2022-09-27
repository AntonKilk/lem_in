/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:59:26 by akilk             #+#    #+#             */
/*   Updated: 2022/09/27 11:27:58 by akilk            ###   ########.fr       */
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

	parse(&farm);
	// print_mtx(&farm);

	preprocess_farm(&farm);
	// print_mtx(&farm);
	printf("FIND SOLUTION\n");

	solve(&farm);
	release(&farm);
	return (0);
}
