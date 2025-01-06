/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoumare <asoumare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:35:39 by asoumare          #+#    #+#             */
/*   Updated: 2024/10/30 19:34:21 by asoumare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void init(t_list **slack, char **av, int i)
{
	*slack = (t_list *)malloc(sizeof(t_list));
	if (!*slack)
		return ;
    (*slack)->philo_nb = atoi (av[1]);
	(*slack)->time2die = atoi (av[2]);
	(*slack)->time2eat = atoi (av[3]);
	(*slack)->time2sleep = atoi (av[4]);
    if (i == 1)
    {
        (*slack)->max_eat = atoi (av[5]);
    }
}