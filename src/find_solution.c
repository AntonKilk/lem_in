/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:30:39 by akilk             #+#    #+#             */
/*   Updated: 2022/09/26 10:01:06 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	get_next_start(t_solution *solution)
{
	int	next;

	next = solution->starts[solution->n_paths - 1];
	solution->starts[solution->n_paths - 1] = -1;
	solution->n_paths--;
	return (next);
}

int	find_length(t_farm *farm, t_solution *solution)
{
	int	length;
	int	i;

	i = solution->starts[solution->n_paths - 1];
	length = 1;
	//for printing:
	// printf("\ncurr start:%s\n", farm->rooms[i]);
	printf("Current path:");
	printf("\n%s-", farm->rooms[farm->start]);
	while(solution->data[i] != farm->end)
	{
		if (solution->data[i] == -1)
			return (error(NULL, "Wrong data in find_lenght()"));
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
	int	*sortedlens;


	//Get rid of all negative values in lengths// create a separate func
	/* new f */
	i = 0;
	int	new_len = 0;
	while (i < farm->max_paths)
	{
		if (t_solution->lengths[i] > 0)
			new_len++;
		i++;
	}
	sortedlens = new_int_arr(new_len);
	i = 0;
	int k = 0;
	while (i < farm->max_paths)
	{
		if (t_solution->lengths[i] > 0)
			sortedlens[k++] = t_solution->lengths[i];
		i++;
	}
	// intcpy(sortedlens, t_solution->lengths + i, new_len);
	bubble_sort(sortedlens, new_len);
	/* new f */

	printf("\nNEW lens:\n");
	for (size_t i = 0; i < new_len; i++)
	{
		printf(" %d ", sortedlens[i]);
	}
	printf("\n");

	// calculate
	result = sortedlens[0];
	d = 1;
	ants = farm->ants;
	i = 0;
	while (i + 1 < new_len)
	{
		p1 = sortedlens[i];
		p2 = sortedlens[i + 1];
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
	free(sortedlens);
	return (result);
}

void	evaluate_solution(t_farm *farm, t_solution *solution, t_best *best)
{

	solution->result = evaluate(farm, solution);
	//for printing
	for (size_t i = 0; i < farm->max_paths; i++)
	{
		if (solution->starts[i] != -1)
			printf("Reached end. Starts:%s\n", farm->rooms[solution->starts[i]]);
		i++;
	}
	printf("RESULT: %d\n", solution->result);
}

void	fill_lengths(int length, t_farm *farm, t_solution *solution)
{
	int	i;
	solution->lengths[solution->n_paths - 1] = length;
	// zero lengths if no starts
	i = 0;
	while (i < farm->max_paths)
	{
		if (solution->starts[i] == -1)
			solution->lengths[i] = -1;
		i++;
	}
}

void	fill_best(t_farm *farm, t_solution *solution, t_best *best)
{
	if (solution->result != 0 && best->result == 0)
	{
		best->result = solution->result;
		intcpy(best->solution, solution->data, farm->rooms_nb);
		intcpy(best->starts, solution->starts, farm->max_paths);
	}
	else if (solution->result < best->result)
	{
		best->result = solution->result;
		intcpy(best->solution, solution->data, farm->rooms_nb);
		intcpy(best->starts, solution->starts, farm->max_paths);
	}
}

int	solve_from(int current, t_farm *farm, t_solution *solution, t_best *best)
{
	int	next;
	int	length;
	int	other;

	next = 0;
	while (next < farm->rooms_nb)
	{
		if(connected(farm, current, next))
		{
			if (solution->data[next] != -1 || next == farm->start)
			{
				next++;
				continue ;
			}
			printf("Trying link %s -> %s\n", farm->rooms[current], farm->rooms[next]);
			if (next == farm->end)
			{
				solution->data[current] = farm->end;
				length = find_length(farm, solution);
				if (!length)
					exit(1);
				fill_lengths(length, farm, solution);
				evaluate_solution(farm, solution, best);
				/* check with current start if there are more paths available */
				solve_from(farm->start, farm, solution, best);
				// if (other < solution->result)
				// 	solution->result = other;
			}
			else
			{
				if (current == farm->start)
					solution->starts[solution->n_paths++] = next;
				else
					solution->data[current] = next;
				solve_from(next, farm, solution, best);
				if (current == farm->start)
					next = get_next_start(solution);
			}
		}
		next++;
		fill_best(farm, solution, best);
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
	farm->start = find_start(farm);
	farm->end = find_end(farm);
	solution = init_solution(farm);
	if(!solution)
		return (error(NULL, "Allocation error in solve()\n"));

	if (!solve_from(farm->start, farm, solution, best))
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
