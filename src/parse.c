/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:47:59 by akilk             #+#    #+#             */
/*   Updated: 2022/08/11 10:44:15 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	parse_ants(char *line, t_farm *farm)
{
	farm->ants = ft_atoi(line);
	if (farm->ants <= 0)
		fprintf(stderr, "Error parsing ants number.");
}

char	*get_room_name(char *line)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	while(line[i] != ' ')
		i++;
	result = ft_strnew(i);
	ft_memcpy(result, line, i);
	return (result);
}

int	parsing_is_valid(size_t rooms, t_farm *farm)
{
	if (farm-> rooms <= 0)
	{
		fprintf(stderr, "No rooms found");
		return (0);
	}
	return (1);
}

void	parse(t_farm *farm)
{
	enum state	line_state;
	char		*line;
	t_lst		*room_lst;
	size_t		count_rooms;

	line = NULL;
	room_lst = NULL;
	count_rooms = 0;
	while (get_next_line(0, &line))
	{
		if (line_state == START)
			farm->start = get_room_name(line);
		else if (line_state == END)
			farm->end = get_room_name(line);
		read_state(&line_state, line);
		if (line_state == ANTS)
			parse_ants(line, farm);
		else if (line_state == LINKS)
			break ;// and parse links in separate function after parsing rooms
		else if (line_state == ROOMS)
		{
			count_rooms++;
			my_lstadd(&room_lst, my_lstnew(get_room_name(line)));
		}
		else if (line_state == ERROR)
			fprintf(stderr, "Error reading line\n%s", line); //rplc
		ft_strdel(&line);
	}
	parse_rooms(count_rooms, room_lst, farm);
	parse_links(count_rooms, &line, farm, &line_state);
	if (!parsing_is_valid(count_rooms, farm))
		fprintf(stderr, "Wrong input."); // rplc
}
	// int i = 0;
	// while (i < count_rooms)
	// {
	// 	printf("room[%d]: %s\n", i, farm->rooms[i]);
	// 	i++;
	// }


	// printf("line: %s\n", line);
	// printf("state: %d\n", line_state);
	// printf("ants: %zu\n", farm->ants);
	// printf("start: %s\n", farm->start);
	// printf("end: %s\n", farm->end);

