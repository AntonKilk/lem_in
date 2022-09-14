/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:58:04 by akilk             #+#    #+#             */
/*   Updated: 2022/09/13 15:01:25 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void ft_swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int bubble_sort(int *tab, int size)
{
    int ii, jj, temp;

    ii = 0;
    while (ii < size - 1)
    {
        jj = size - 1;
        while (jj > ii)
        {
            if (tab[jj-1] > tab[jj])
            {
                ft_swap(&tab[jj-1], &tab[jj]);
            }
            jj--;
        }
        ii++;
    }
    return *tab;
}
