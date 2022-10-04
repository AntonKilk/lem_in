/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:20:48 by akilk             #+#    #+#             */
/*   Updated: 2022/10/04 15:23:09 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define MAX_INT 2147483647
# define OK 1

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

typedef enum	room_state
{
	FREE,
	VISITED,
	USED,
	PASS,
	LEAVE
}				t_room_state;

typedef struct s_room_info
{
	t_room_state	state;
	int				prev;
	int				next;
	int				distance;
}			t_room_info;

typedef struct s_solution
{
	int			n_paths;
	int			result;
	int			old_path_used;
	t_room_info	*room;
	int			*data;
	int			*lengths;
	int			*starts;
}			t_solution;

typedef struct s_best
{
	int	result;
	int	*solution;
	int	*starts;
}			t_best;

typedef struct s_queue
{
	int	head;
	int	tail;
	int	data[0];
}			t_queue;

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
void	set_link(t_farm *farm, int from, int to, int len);
int	find_end(t_farm *farm);
int	find_start(t_farm *farm);

/* find_solution.c */
int	solve(t_farm *farm);
int	solve_from(int current, t_farm *farm, t_solution *solution, t_best *best);

/* optimize.c */
int	preprocess_farm(t_farm *farm);

/* free.c */
void	release(t_farm *farm);
void	free_solution(t_solution *solution, t_best *best);

/* init.c */
t_solution	*init_solution(t_farm *farm);
t_best	*init_best(t_farm *farm);
void	init_room_info(t_farm *farm, t_room_info *info);

/* bfs.c */
int	bfs(t_farm *farm, t_solution *solution);
int	track_back(t_farm *farm, t_solution *solution);

/* queue helpers.c */
t_queue *new_queue(int size);
void	put(t_queue *q, int item);
int	get(t_queue *q);
int	is_empty(t_queue *q);
void	release_queue(t_queue *q);

#endif
