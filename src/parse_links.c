/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:29:44 by akilk             #+#    #+#             */
/*   Updated: 2022/08/11 11:31:26 by akilk            ###   ########.fr       */
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
	farm->links[h * size + w] = '1';
	farm->links[w * size + h] = '1';
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

/* PRINTS MATRIX OF LINKS,
	where room[i] connected to room[j] if links[i][j] == 1 */
void	print_mtx(size_t size, t_farm *farm)
{
	printf("print matrix with size: %zu\n", size);
	int i = 0;
	printf("|-> ");
	while (i < size)
		printf("%3.3s", farm->rooms[i++]);
	printf("\n");
	i = 0;
	int k = 0;
	printf("%4.4s", farm->rooms[k++]);
	while(i < size * size)
	{
		printf("%3c", farm->links[i]);
		if (i % size== size - 1)
		{
			printf("\n");
			if (k < size)
				printf("%4.4s", farm->rooms[k++]);
		}
		i++;
	}
}

void	parse_links(size_t size, char **line, t_farm *farm, enum state *state)
{
	farm->links = ft_strnew(size * size);
	ft_memset(farm->links, '0', size * size);
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
	print_mtx(size, farm);
}
