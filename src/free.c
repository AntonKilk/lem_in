/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:27:04 by akilk             #+#    #+#             */
/*   Updated: 2022/09/27 11:32:09 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	free_solution(t_solution *solution, t_best *best)
{
	free(solution->data);
	free(solution->lengths);
	free(solution->starts);
	free(best->solution);
	free(best->starts);
	best = NULL;
	solution = NULL;
}

void	release(t_farm *farm)
{
	free(farm->start_name);
	free(farm->end_name);
	ft_free_tab(farm->rooms, farm->rooms_nb);
	free(farm->links);
	farm = NULL;
}
