/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:51:39 by akilk             #+#    #+#             */
/*   Updated: 2022/08/01 14:53:16 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	is_number(char *line)
{
	while (*line)
	{
		if (!ft_isdigit(*line))
			return (0);
		line++;
	}
	return (1);
}

int	is_room(char *line)
{
	if (line[0] == '#' || line[0] == 'L')
		return 0;
	if (ft_count_words(line, ' ') != 3)
		return 0;
	return (1);
}

int	is_link(char *line)
{
	if (ft_count_words(line, '-') != 2)
		return 0;
	return (1);
}

void	read_state(enum state *line_state, char *line)
{
	if (line[0] == '#' && line[1] != '#')
		*line_state = COMMENT;
	else if (is_number(line))
		*line_state = ANTS;
	else if (!ft_strcmp(line, "##start"))
		*line_state = START;
	else if (!ft_strcmp(line, "##end"))
		*line_state = END;
	else if (is_room(line))
		*line_state = ROOMS;
	else if (is_link(line))
		*line_state = LINKS;
	else
		*line_state = ERROR;
}
