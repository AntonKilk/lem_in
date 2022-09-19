/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:20:48 by akilk             #+#    #+#             */
/*   Updated: 2022/09/19 10:45:26 by akilk            ###   ########.fr       */
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
	char	*start;
	char	*end;
	char	**rooms;
	int		*links;
}				t_farm;

// typedef struct s_queue
// {
// 	int	head;
// 	int	tail;
// 	int	data[0];
// }			t_queue;

typedef struct s_solution
{
	int	n_paths;
	int	*data;
	int	*lengths;
	int	*starts;
}			t_solution;

// typedef struct s_path
// {
// 	int		len;
// 	t_list	*path;
// }			t_path;

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
int	error(char **str, char *msg);

/* parse_rooms.c */
t_lst	*my_lstnew(void const *content);
void	my_lstadd(t_lst **alst, t_lst *new);
void	parse_rooms(t_lst *room_lst, t_farm *farm);

/* parse_links.c */
void	parse_links(char **line, t_farm *farm, enum state *state);

/* print_mtx.c */
void	print_mtx(t_farm *farm);

/* find_path.c */
int	find_all_paths(t_farm *farm, t_list **paths);

/* find_path_helpers.c */
void	zero_arr(int *result, int size);
int	*new_int_arr(int size);
int	not_in_list(int nb, t_list *path);
void	add2list(t_list **paths, t_list *path, int len);

/* run_ants.c */
void	print_paths(t_farm *farm, t_list *paths, int found_paths);
void	calculate_routes(t_farm *farm, t_list *paths, int found_paths);

/* find_solution.c */
int	solve(t_farm *farm);
int	solve_from(int current, t_farm *farm, t_solution *solution);

/* bubble_sort.c */
int bubble_sort(int *tab, int size);

#endif
