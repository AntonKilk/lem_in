/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:20:48 by akilk             #+#    #+#             */
/*   Updated: 2022/07/28 16:04:21 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define BUFF_SIZE 1000000

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_farm
{
	size_t	ants;
	size_t	room_nb;
	size_t	start;
	size_t	end;
	char	*room_name;
	char	**links;
}				t_farm;

void	parse(char *buf, t_farm *farm);
int		main(void);

/* libft */
int	ft_atoi(const char *str);
int	ft_isdigit(int c);

#endif
