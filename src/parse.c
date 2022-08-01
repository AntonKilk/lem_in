/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:47:59 by akilk             #+#    #+#             */
/*   Updated: 2022/08/01 15:03:30 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	parse_ants(char *line, t_farm *farm)
{
	farm->ants = ft_atoi(line);
	if (farm->ants <= 0)
		fprintf(stderr, "Error parsing ants number.\n");
}

void	parse_rooms(char *line, t_farm *farm)
{
	static int	i;

	i = 0;
	farm->room_names[i] = ft_strdup(line);
	if (farm->ants <= 0)
		fprintf(stderr, "Error parsing ants number.\n");
	i++;
}

void	parse(t_farm *farm)
{
	enum state	line_state;
	char		*line;

	line = NULL;
	while (get_next_line(0, &line))
	{
		read_state(&line_state, line);
		if (line_state == ANTS)
			parse_ants(line, farm);
		else if (line_state == ROOMS)
			parse_rooms(line, farm);
		// else if (state == LINKS)
		// 	parse_links(&line, farm);
		// else if (state == START)
		// 	parse_command(&line, farm);
		else if (line_state == ERROR)
			fprintf(stderr, "Error reading line |%s|.\n", line);
		printf("line: %s\n", line);
		printf("state: %d\n", line_state);
	}
	printf("ants: %zu\n", farm->ants);
	ft_strdel(&line);
}
