/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:58:04 by akilk             #+#    #+#             */
/*   Updated: 2022/09/22 09:21:06 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int bubble_sort(int *tab, int size)
{
    int i, j, temp;

    i = 0;
    while (i < size - 1)
    {
        j = size - 1;
        while (j > i)
        {
            if (tab[j-1] > tab[j])
            {
                ft_swap(&tab[j-1], &tab[j]);
            }
            j--;
        }
        i++;
    }
    return *tab;
}
