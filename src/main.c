/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoumare <asoumare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:22:33 by asoumare          #+#    #+#             */
/*   Updated: 2025/01/06 18:56:51 by asoumare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int ac, char **av)
{
	t_list	*slack;
	int	i = 1;

	slack = NULL;
	if (ac != 5 && ac != 6)
		return (0);
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
		{
			printf("null\n");
			return (1);
		}
		i++;
	}
	if (ac == 6)
		i = 1;
	init(&slack, av , i);
	printf("%d -> %d -> %d -> %d -> %d ", slack->philo_nb, slack->time2die, slack->time2eat, slack->time2sleep, slack->max_eat);
	printf("fin\n");
}