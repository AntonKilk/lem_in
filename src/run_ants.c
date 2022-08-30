/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 08:12:56 by akilk             #+#    #+#             */
/*   Updated: 2022/08/30 08:30:11 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	print_paths(t_farm *farm, t_list *paths)
{
	t_list *path_ptr;
	t_list *room_ptr;

	path_ptr = paths;
	while (path_ptr)
	{
		room_ptr = *(t_list **) path_ptr->content;
		while (room_ptr)
		{
			printf("%s", farm->rooms[*(int *)room_ptr->content]);
			if (room_ptr->next)
				printf(" -> ");
			else
				printf("\n");
			room_ptr = room_ptr->next;
		}
		path_ptr = path_ptr->next;
	}
}

void	run_ants(t_farm *farm, t_list *paths)
{
	printf("ants nb: %zu\n", farm->ants);
	int	i;

	i = 1;
	while (i <= farm->ants)
	{
		printf("L%d-\n", i);
		i++;
	}

}
