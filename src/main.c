/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:59:26 by akilk             #+#    #+#             */
/*   Updated: 2022/07/28 16:03:59 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	read_farm(char *buf)
{
	int	ret;

	ret = read(0, buf, BUFF_SIZE);
	if (ret < 0)
		fprintf(stderr, "Error reading in read_farm");//replace
	buf[ret] = '\0';
	printf("%s\n", buf);
}

int	main(void)
{
	char	buf[BUFF_SIZE];
	t_farm	farm;

	read_farm(buf);
	parse(buf, &farm);
	return (0);
}
