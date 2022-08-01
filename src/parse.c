/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:47:59 by akilk             #+#    #+#             */
/*   Updated: 2022/08/01 20:32:00 by akilk            ###   ########.fr       */
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

int	parsing_is_valid(t_farm *farm)
{
	if (farm-> rooms_total <= 0)
	{
		fprintf(stderr, "No rooms found");
		return (0);
	}
	return (1);
}

void	parse_room(char *line, t_farm *farm)
{
	char	*name;

	farm->rooms_total++;
	name = get_room_name(line);
	//validate_coordinates
}

void	parse(t_farm *farm)
{
	enum state	line_state;
	char		*line;

	line = NULL;
	farm->rooms_total = 0;
	while (get_next_line(0, &line))
	{
		if (line_state == START)
			farm->start = get_room_name(line);
		else if (line_state == END)
			farm->end = get_room_name(line);
		read_state(&line_state, line);
		if (line_state == ANTS)
			parse_ants(line, farm);
		else if (line_state == ROOMS)
			parse_room(line, farm);
		// else if (state == LINKS)
		// 	parse_links(&line, farm);
		// else if (state == START)
		// 	parse_command(&line, farm);
		else if (line_state == ERROR)
			fprintf(stderr, "Error reading line\n%s", line); //rplcs
		printf("line: %s\n", line);
		printf("state: %d\n", line_state);
		ft_strdel(&line);
	}
	printf("ants: %zu\n", farm->ants);
	printf("start: %s\n", farm->start);
	printf("end: %s\n", farm->end);

	// int i = 0;
	// while (i < farm->rooms_total)
	// {
	// 	printf("%d:%s"farm->room_nb[i], farm->room_name[i]);
	// 	i++;
	// }
	if (!parsing_is_valid(farm))
		fprintf(stderr, "Wrong input."); // rplc
}
