/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:47:59 by akilk             #+#    #+#             */
/*   Updated: 2022/09/27 12:51:59 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lem_in.h"

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

int	parsing_is_valid(t_farm *farm)
{
	if (farm->rooms_nb <= 0)
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

	line = NULL;
	room_lst = NULL;
	farm->rooms_nb = 0;
	while (get_next_line(0, &line))
	{
		if (line_state == START)
			farm->start_name = get_room_name(line);
		else if (line_state == END)
			farm->end_name = get_room_name(line);
		read_state(&line_state, line);
		if (line_state == ANTS)
			parse_ants(line, farm);
		else if (line_state == LINKS)
			break ;// and parse links in separate function after parsing rooms
		else if (line_state == ROOMS)
		{
			farm->rooms_nb++;
			my_lstadd(&room_lst, my_lstnew(get_room_name(line)));
		}
		else if (line_state == ERROR)
			fprintf(stderr, "Error reading line\n%s", line); //rplc
		ft_strdel(&line);
	}
	parse_rooms(room_lst, farm);
	parse_links(&line, farm, &line_state);
	farm->start = find_start(farm);
	farm->end = find_end(farm);
	if (!parsing_is_valid(farm))
		fprintf(stderr, "Wrong input."); // rplc
}

