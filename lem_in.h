/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:20:48 by akilk             #+#    #+#             */
/*   Updated: 2022/09/26 07:18:52 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define MAX_INT 2147483647

# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_lst
{
	void			*content;
	struct s_lst	*next;
}					t_lst;

typedef struct s_farm
{
	int		ants;
	int		rooms_nb;
	int		start_links;
	int		max_paths;
	int		start;
	char	*start_name;
	int		end;
	char	*end_name;
	char	**rooms;
	int		*links;
}				t_farm;

typedef struct s_solution
{
	int	n_paths;
	int	result;
	int	*data;
	int	*lengths;
	int	*starts;
}			t_solution;

typedef struct s_best
{
	int	result;
	int	*solution;
	int	*starts;
}			t_best;


enum	state
{
	COMMENT,
	ANTS,
	START,
	END,
	ROOMS,
	LINKS,
	ERROR
};

void	parse(t_farm *farm);
void	read_state(enum state *line_state, char *line);
int		main(void);
int		error(char **str, char *msg);

/* parse_rooms.c */
t_lst	*my_lstnew(void const *content);
void	my_lstadd(t_lst **alst, t_lst *new);
void	parse_rooms(t_lst *room_lst, t_farm *farm);

/* parse_links.c */
void	parse_links(char **line, t_farm *farm, enum state *state);

/* print_mtx.c */
void	print_mtx(t_farm *farm);
void	print_path(t_farm *farm, t_solution *solution, t_best *best);

/* find_solution_helpers.c */
void	intcpy(int *dest, int *src, int size);
void	zero_arr(int *result, int size);
int	*new_int_arr(int size);
int	max_paths_nb(t_farm *farm);
int	count_links(t_farm *farm, int node);
int	connected(t_farm *farm, int from, int to);
int	find_end(t_farm *farm);
int	find_start(t_farm *farm);
t_solution	*init_solution(t_farm *farm);
t_best	*init_best(t_farm *farm);

/* find_solution.c */
int	solve(t_farm *farm);
int	solve_from(int current, t_farm *farm, t_solution *solution, t_best *best);

/* bubble_sort.c */
int bubble_sort(int *tab, int size);

#endif
