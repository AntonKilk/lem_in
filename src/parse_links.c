/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:29:44 by akilk             #+#    #+#             */
/*   Updated: 2022/08/25 08:54:42 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	fill_links(size_t size, t_farm *farm, char *fst, char *snd)
{
	int	w;
	int	h;

	w = 0;
	while (ft_strcmp(farm->rooms[w], fst))
	{
		if (w == size - 1)
		{
			fprintf(stderr, "No link found");
			return ;
		}
		w++;
	}
	h = 0;
	while (ft_strcmp(farm->rooms[h], snd))
	{
		if (h == size - 1)
		{
			fprintf(stderr, "No link found");
			return ;
		}
		h++;
	}
	farm->links[h * size + w] = 1;
	farm->links[w * size + h] = 1;
}

void	get_links(size_t size, char *line, t_farm *farm)
{
	char	*fst;
	char	*snd;
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strdup(line);
	fst = tmp;
	while(tmp[++i] != '-')
		fst[i] = tmp[i];
	fst[i] = '\0';
	snd = &tmp[i + 1];
	//printf("f:%s, s:%s\n", fst, snd);
	ft_strdel(&tmp);
	fill_links(size, farm, fst, snd);
}

void	parse_links(char **line, t_farm *farm, enum state *state)
{
	size_t	size;

	size = farm->rooms_nb;
	farm->links = (int *)malloc(sizeof (int *) * (size * size));
	if (!farm->links)
		return ; // add error func
	ft_memset(farm->links, 0, size * size);

	while (*state == LINKS)
	{
		read_state(state, *line);
		// printf("%s\n", *line);
		if (*state != LINKS)
			break ;
		get_links(size, *line, farm);
		ft_strdel(line);
		if (!get_next_line(0, line))
			break ;
	}
}
