/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:30:39 by akilk             #+#    #+#             */
/*   Updated: 2022/09/14 12:56:11 by akilk            ###   ########.fr       */
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

int	find_lengths(t_solution *solution, t_farm *farm)
{
	int	length;
	int	i;

	i = 0;
	length = 0;
	// printf("\n");
	while(i < farm->rooms_nb)
	{
		// printf("%d ", solution->data[i]);
		if (solution->data[i] != -1)
			length++;
		i++;
	}
	// printf("\n");
	return(length);
}

void	print_path(t_solution *solution, t_farm *farm)
{
	int	i;

	i = 0;
	printf("\n");
	while(i < farm->rooms_nb)
	{

		if (solution->data[i] != -1)
			printf("%s-", farm->rooms[solution->data[i]]);
		i++;
	}
	printf("\n");
}

int	solve_from(int current, t_farm *farm, t_solution *solution)
{
	int	start;
	int	end;
	int	next;
	int	result = 0;

	start = find_start(farm);
	end = find_end(farm);
	next = 0;
	if (!current)
		current = start;
	while (next < farm->rooms_nb)
	{
		if(connected(farm, current, next))
		{
			if (solution->data[next] != -1 || next == start)
			{
				next++;
				continue ;
			}
			// printf("Trying link %s -> %s\n", farm->rooms[current], farm->rooms[next]);
			if (next == end)
			{
				printf("END REACHED\n");
				printf("path length: %d\n", find_lengths(solution, farm));
				print_path(solution, farm);
				return (0);
				// bubble_sort(solution->lengths)
				// solution->data[current] = end;
				// result = evaluate_solution(solution->starts, solution);
			}
			else
			{
				// if (current == start)
				// {
				// 	int k = 0;
				// 	while (solution->starts[k] != -1)
				// 	{
				// 		next = solution->starts[k] + 1;
				// 		k++;
				// 	}
				// }
				// else
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
