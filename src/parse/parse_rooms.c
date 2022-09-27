/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:04:17 by akilk             #+#    #+#             */
/*   Updated: 2022/09/27 12:41:12 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lem_in.h"

t_lst	*my_lstnew(void const *content)
{
	t_lst	*ptr;
	size_t	size;

	size = ft_strlen(content);
	ptr = (t_lst *)malloc(sizeof(t_lst));
	if (!ptr)
		return (NULL);
	if (content == NULL)
	{
		ptr->content = NULL;
		ptr->next = NULL;
		return (ptr);
	}
	ptr->content = ft_memalloc(size);
	if (!ptr->content)
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(ptr->content, content, size);
	ptr->next = NULL;
	return (ptr);
}

void	my_lstadd(t_lst **alst, t_lst *new)
{
	if (alst == NULL)
		return ;
	new->next = *alst;
	*alst = new;
}

void	parse_rooms(t_lst *room_lst, t_farm *farm)
{
	int	size;

	size = farm->rooms_nb;
	farm->rooms = (char **)malloc(sizeof (char *) * (size + 1));
	farm->rooms[size] = NULL;
	if (!farm->rooms)
		fprintf(stderr, "Error allocating farm->rooms in parse_rooms()"); //
	while (room_lst)
	{
		size--;
		farm->rooms[size] = ft_strdup((char *)room_lst->content);
		free(room_lst->content);
		room_lst = room_lst->next;
	}
	free(room_lst);
}

