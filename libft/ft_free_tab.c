/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 09:54:06 by akilk             #+#    #+#             */
/*   Updated: 2022/09/27 13:05:11 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_tab(char **tab, int x)
{
	while (x >= 0)
	{
		if (tab[x])
			free (tab[x]);
		x--;
	}
	free (tab);
	return (NULL);
}
