/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:24:25 by akilk             #+#    #+#             */
/*   Updated: 2022/08/11 15:28:22 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

// char	*find_neighbours(int i, t_farm *farm)
// {
// 	if (farm->links[i] == '1')
// 		return (farm->rooms[i]);
// 	else
// }

void	bfs(t_farm *farm)
{
	int		i;
	int		k;
	char	**visited;

	i = 0;
	visited = (char **)malloc(sizeof (char *) * (farm->rooms_nb + 1));
	if (!visited)
		return ;//add error
	k = 0;
	while (i < farm->rooms_nb)
	{
		if (farm->links[i] == '1')
		{
			visited[k] = ft_strdup(farm->rooms[i]);
			printf("%s\n", visited[k]);
			k++;
		}
		i++;
	}
}
