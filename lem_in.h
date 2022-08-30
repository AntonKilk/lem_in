/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:20:48 by akilk             #+#    #+#             */
/*   Updated: 2022/08/30 08:28:28 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
// # define BUFF_SIZE 1000000

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
	size_t	ants;
	size_t	rooms_nb;
	char	*start;
	char	*end;
	char	**rooms;
	int		*links;
}				t_farm;

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

/* parse_rooms.c */
t_lst	*my_lstnew(void const *content);
void	my_lstadd(t_lst **alst, t_lst *new);
void	parse_rooms(t_lst *room_lst, t_farm *farm);

/* parse_links.c */
void	parse_links(char **line, t_farm *farm, enum state *state);

/* print_mtx.c */
void	print_mtx(t_farm *farm);

/* bfs.c */
int	find_end(t_farm *farm);
int	is_connected(t_farm *farm, int fst, int snd);
int	bfs(t_farm *farm, int *distances);

/* queue helpers.c */
t_queue *new_queue(int size);
void	put(t_queue *q, int item);
int	get(t_queue *q);
int	is_empty(t_queue *q);
void	release_queue(t_queue *q);

/* find_paths.c */
void	find_all_paths(t_farm *farm, t_list **paths);

/* run_ants.c */
void	run_ants(t_farm *farm, t_list *paths);
void	print_paths(t_farm *farm, t_list *paths); // for testing purpose

#endif
