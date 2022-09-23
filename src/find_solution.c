/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:30:39 by akilk             #+#    #+#             */
/*   Updated: 2022/09/23 11:51:00 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	get_next_start(t_solution *solution)
{
	int	k;
	int	next;

	next = 0;
	k = 0;
	while (solution->starts[k] != -1)
	{
		next = solution->starts[k];
		k++;
	}
	return (next);
}

int	find_lengths(t_farm *farm, t_solution *solution)
{
	int	length;
	int	i;

	int end = find_end(farm);
	i = solution->starts[solution->n_paths - 1];
	length = 1;
	//for printing:
	printf("\ncurr start:%s\n", farm->rooms[i]);
	printf("\n%s-", farm->start);
	while(solution->data[i] != end)
	{
		if (solution->data[i] == -1)
			return (error(NULL, "Wrong data in find_lenghts()"));
		length++;
		// for printing:
		printf("%s-", farm->rooms[i]);
		i = solution->data[i];
	}
	printf("%s-%s", farm->rooms[i], farm->rooms[solution->data[i]]);
	printf("\nLength:%d\n", length);
	return (length);
}

int	evaluate(t_farm *farm, t_solution *t_solution)
{
	int	ants;
	int	d;
	int	result;
	int	i;
	int	p1;
	int	p2;
	int	moved;

	//This is because lengts are sorted and
	// can have -1 in the beginning
	i = 0;
	while (t_solution->lengths[i] == -1)
		i++;
	result = t_solution->lengths[i];
	d = 1;
	ants = farm->ants;
	while (i + 1 < farm->max_paths)
	{
		p1 = t_solution->lengths[i];
		p2 = t_solution->lengths[i + 1];
		moved = (p2 - p1) * d;
		if (ants <= moved)
			break ;
		ants -= moved;
		result += p2 - p1;
		d += 1;
		i++;
	}
	result += ants / d;
	if (ants % d)
		result += 1;
	printf("result in evaluate: %d\n", result);
	return (result);
}

int	evaluate_solution(t_farm *farm, t_solution *solution, t_best *best)
{
	int		result;

	result = evaluate(farm, solution);
	if (result < best->result)
	{
		best->result = result;
		intcpy(best->solution, solution->data, farm->rooms_nb);
		intcpy(best->starts, solution->starts, farm->max_paths);
	}
	//for printing
	for (size_t i = 0; i < farm->max_paths; i++)
	{
		if (solution->starts[i] != -1)
			printf("Reached end. Starts:%s\n", farm->rooms[solution->starts[i]]);
		i++;
	}
	printf("\nRESULT: %d\n", result);
	return (result);
}

void	sort_lengths(int length, t_farm *farm, t_solution *solution)
{
	int l;

	l = 0;
	while (l < farm->max_paths)
	{
		if (solution->lengths[l++] == -1)
			break ;
	}
	solution->lengths[l - 1] = length;
	bubble_sort(solution->lengths, farm->max_paths);
}

int	solve_from(int current, t_farm *farm, t_solution *solution, t_best *best)
{
	int	next;
	int	start;
	int	end;
	int length;

	start = find_start(farm);
	end = find_end(farm);
	next = 0;
	while (next < farm->rooms_nb)
	{
		if(connected(farm, current, next))
		{
			if (solution->data[next] != -1 || next == start)
			{
				next++;
				continue ;
			}
			printf("Trying link %s -> %s\n", farm->rooms[current], farm->rooms[next]);
			if (next == end)
			{
				solution->data[current] = end;
				length = find_lengths(farm, solution);
				if (!length)
					exit(1);
				sort_lengths(length, farm, solution);
				evaluate_solution(farm, solution, best);
				solve_from(start, farm, solution, best);
				// if (other < result)
				// 	result = other;
			}
			else
			{
				if (current == start)
					solution->starts[solution->n_paths++] = next;
				else
					solution->data[current] = next;
				solve_from(next, farm, solution, best);
				if (current == start)
					solution->starts[solution->n_paths--] = -1;
			}
		}
		next++;
	}
	solution->data[current] = -1;
	return (1);
}

int	solve(t_farm *farm)
{
	int			start;
	t_solution	*solution;
	t_best	*best;

	best = init_best(farm);
	start = find_start(farm);
	solution = init_solution(farm);
	if(!solution)
		return (error(NULL, "Allocation error in solve()\n"));

	if (!solve_from(start, farm, solution, best))
		return (error(NULL, "No solution found"));
	printf("Best RESULT in solve(): %d\n", best->result);
	printf("best->solution arr\n");
	for (size_t i = 0; i < farm->rooms_nb; i++)
	{
		printf("%3d", best->solution[i]);
	}
	printf("\nbest->starts arr\n");
	for (size_t i = 0; i < farm->max_paths; i++)
	{
		printf("%3s", farm->rooms[best->starts[i]]);
	}
	printf("\nPath(s) used:\n");
	print_path(farm, solution, best);

	return (1);
}
