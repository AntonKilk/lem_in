/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:47:59 by akilk             #+#    #+#             */
/*   Updated: 2022/07/28 16:20:36 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	parse_ants(char *buf, t_farm *farm)
{
	farm->ants = 0;
	while(ft_isdigit(*buf))
	{
		farm->ants = farm->ants * 10 + (*buf - '0');
		buf++;
	}
	if (farm->ants <= 0)
		fprintf(stderr, "Error parsing ants number.");
	if (*buf != '\n')
		fprintf(stderr, "Error after ants number.");
	buf++;
}

void	parse_commands(char *buf)
{
	char	*tmp_p;

	tmp_p = buf;
	while (1)
	{
		if (*tmp_p == '#')

	}
}

//parse rooms

//parse links to matrix

void	parse(char *buf, t_farm *farm)
{
	parse_ants(buf, farm);
	parse_commands();
}
