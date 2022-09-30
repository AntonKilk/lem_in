/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:27:04 by akilk             #+#    #+#             */
/*   Updated: 2022/09/27 13:15:31 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

char	**free_tab(char **tab, int x)
{
	while (x >= 0)
	{
		if (tab[x])
			free (tab[x]);
		x--;
	}
	free (tab);
	return (NULL);
}

void	free_solution(t_solution *solution, t_best *best)
{
	free(solution->data);
	free(solution->lengths);
	free(solution->starts);
	free(best->solution);
	free(best->starts);
}

void	release(t_farm *farm)
{
	free(farm->start_name);
	free(farm->end_name);
	free_tab(farm->rooms, farm->rooms_nb);
	free(farm->links);
}
