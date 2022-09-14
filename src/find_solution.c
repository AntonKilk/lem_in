/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:30:39 by akilk             #+#    #+#             */
/*   Updated: 2022/09/14 10:03:25 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	find_start(t_farm *farm)
{
	size_t	i;

	i = 0;
	while (i < farm->rooms_nb)
	{
		if(!ft_strcmp(farm->start, farm->rooms[i]))
			break;
		i++;
	}
	return (i);
}

int	find_end(t_farm *farm)
{
	size_t	i;

	i= 0;
	while (i < farm->rooms_nb)
	{
		if(!ft_strcmp(farm->end, farm->rooms[i]))
			break;
		i++;
	}
	return (i);
}

int	connected(t_farm *farm, int from, int to)
{
	return (farm->links[from * farm->rooms_nb + to]);
}

int	count_links(t_farm *farm, int node)
{
	int *row;
	int	sum;
	int	i;

	i = 0;
	sum = 0;
	row = farm->links + node * farm->rooms_nb;
	while (i < farm->rooms_nb)
	{
		sum += row[i];
		i++;
	}
	return (sum);
}

void	add2arr(t_solution *solution, int next, int length)
{
	int i = 0;

	while(i < length)
	{
		if (solution->starts[i] == -1)
		{
			solution->starts[i] = next;
			return ;
		}
		i++;
	}
}

int	solve_from(int current, t_farm *farm, t_solution *solution)
{
	int	start;
	int	end;
	int	next;
	int result = 0;
	int links = count_links(farm, start);

	start = find_start(farm);
	end = find_end(farm);
	if (!current)
		current = start;
	next = 0;
	while (next < farm->rooms_nb)
	{
		if(connected(farm, current, next))
		{
			if (solution->data[next] != -1 || next== start)
			{
				next++;
				continue ;
			}
			printf("Trying link %s -> %s\n", farm->rooms[current], farm->rooms[next]);
			if (next == end)
			{
				printf("END REACHED\n");
				return (0);
				// bubble_sort(solution->lengths)
				// solution->data[current] = end;
				// result = evaluate_solution(solution->starts, solution);
			}
			else
			{
				if (current == start)
					add2arr(solution, next, links);
				else
					solution->data[current] = next;

				result = solve_from(next, farm, solution); //infinite loop?
				if (current == start)
				{
					solution->starts[solution->n_paths] = -1;
					solution->n_paths--;
				}
				else
					solution->data[current] = -1;
			}

		}
		next++;
	}

	//solution to solution->data
	//starts to solution->starts
	return (0);
}

int	max_paths_nb(t_farm *farm)
{
	int	start = find_start(farm);
	int	end = find_end(farm);

	return (ft_min(count_links(farm, start), count_links(farm, end)));
}

int	solve(t_solution *solution, t_farm *farm)
{
	int result;

	solution = (t_solution *)malloc(sizeof(t_solution *));
	solution->data = new_int_arr(farm->rooms_nb);
	solution->n_paths = 0;
	solution->starts = new_int_arr(max_paths_nb(farm));
	solution->lengths = new_int_arr(max_paths_nb(farm));
	result = solve_from(0, farm, solution);
	printf("RESULT %d\n", result);
	return (0);
}
