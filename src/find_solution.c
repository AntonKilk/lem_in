/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:30:39 by akilk             #+#    #+#             */
/*   Updated: 2022/09/19 10:57:35 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	find_start(t_farm *farm)
{
	int	i;

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
	int	i;

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

int	max_paths_nb(t_farm *farm)
{
	int	start = find_start(farm);
	int	end = find_end(farm);

	return (ft_min(count_links(farm, start), count_links(farm, end)));
}

void	find_lengths(t_solution *solution, t_farm *farm)
{
	int	length;
	int	i;
	int	k;

	i = 0;
	length = 0;
	//for printing:
	printf("%s-", farm->start);
	int flag = 0;
	int end = find_end(farm);
	printf("LINE %d\n", __LINE__);
	while(i < farm->rooms_nb)
	{
		if (solution->data[i] != -1)
		{
			// for printing:
			if (flag == 0)
			{
				printf("%s-", farm->rooms[i]);
				flag = 1;
			}
			length++;
			printf("%s", farm->rooms[solution->data[i]]);
			if (solution->data[i] != end)
				printf("-");
		}
		i++;
	}
	printf("\n");
	k = 0;
	while (solution->lengths[k] != -1)
		k++;
	solution->lengths[k] = length + 1;
}

int	get_next_from_starts(t_solution *solution)
{
	int	k;
	int	next;

	next = 0;
	k = 0;
	while (solution->starts[k] != -1)
	{
		next = solution->starts[k] + 1;
		k++;
	}
	return (next);
}

void	print_path(t_solution *solution, t_farm *farm)
{
	int	i;

	i = 0;
	while(i < farm->rooms_nb)
	{
		if (solution->data[i] != -1)
			printf("%s-%s\n", farm->rooms[i], farm->rooms[solution->data[i]]);
		i++;
	}
	printf("%s\n", farm->end);
}

int	evaluate()
{
	int result = MAX_INT;

	return (result);
}

int	evaluate_solution(t_farm *farm, t_solution *solution)
{
	int result = MAX_INT;
	int	max_paths = max_paths_nb(farm);
	bubble_sort(solution->lengths, max_paths);
	// result = evaluate(solution->lengths);
	for (size_t i = 0; i < max_paths; i++)
	{
		if (solution->starts[i] != -1)
			printf("Reached end. Starts:%s\n", farm->rooms[solution->starts[i]]);
		i++;
	}

	int i = 0;
	while (solution->starts[i] != -1)
		i++;
	int other = solve_from(solution->starts[i - 1], farm, solution);
	return (result);
}

// for (size_t i = 0; i < max_paths; i++)
// {
// 	if (solution->lengths[i] != -1)
// 		printf("PATH LENGTH is %d\n", solution->lengths[i]);
// }

int	solve_from(int current, t_farm *farm, t_solution *solution)
{
	int	start;
	int	end;
	int	next;
	int	result;
	int	length;

	result = MAX_INT;
	start = find_start(farm);
	end = find_end(farm);
	next = 0;

	for (size_t i = 0; i < farm->rooms_nb; i++)
	{
		printf("d:%d\n", solution->data[i]);
	}

	// while (next < farm->rooms_nb)
	// {
	// 	if(connected(farm, current, next))
	// 	{
	// 		if (solution->data[next] != -1 || next == start)
	// 		{
	// 			next++;
	// 			continue ;
	// 		}
	// 		printf("Trying link %s -> %s\n", farm->rooms[current], farm->rooms[next]);
	// 		if (next == end)
	// 		{
	// 			// print_path(solution, farm);
	// 			printf("LINE %d\n", __LINE__);
	// 			solution->data[current] = next;
	// 			find_lengths(solution, farm);
	// 			//vot tut nado peredat tekushij path
	// 			result = evaluate_solution(farm, solution);
	// 		}
	// 		else
	// 		{
	// 			if (current == start)
	// 			{
	// 				solution->starts[solution->n_paths] = next;
	// 				solution->n_paths++;
	// 			}
	// 			else
	// 				solution->data[current] = next;
	// 			result = solve_from(next, farm, solution);
	// 			// printf("current after recursion: %s\n", farm->rooms[current]);
	// 			if (current == start)
	// 			{
	// 				next = get_next_from_starts(solution);
	// 			}
	// 			else
	// 			{
	// 				solution->data[current] = -1;
	// 			}
	// 		}
	// 	}
	// 	next++;
	// }
	return (0);
}

int	solve(t_farm *farm)
{
	int	result;
	int	start;
	int	start_links;
	t_solution *solution;

	solution = (t_solution *)malloc(sizeof(t_solution *));
	ft_bzero(solution, sizeof(*solution));
	result = MAX_INT;
	start = find_start(farm);
	start_links = count_links(farm, start);
	printf("rooms nb: %d\n", farm->rooms_nb);
	solution->data = new_int_arr(farm->rooms_nb);
	solution->n_paths = 0;
	solution->starts = new_int_arr(start_links);
	solution->lengths = new_int_arr(max_paths_nb(farm));
	result = solve_from(start, farm, solution);
	printf("RESULT %d\n", result);
	return (0);
}

	//get starts:
	// int k = 0;
	// int i = 0;
	// while (k < farm->rooms_nb)
	// {
	// 	if (connected(farm, start, k))
	// 	{
	// 		solution->starts[i] = k;
	// 		i++;
	// 	}
	// 	k++;
	// }
