/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoumare <asoumare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:25:21 by asoumare          #+#    #+#             */
/*   Updated: 2025/01/28 19:33:07 by asoumare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat(pthread_mutex_t mutex, t_slack *philo ,t_list *slack)
{
	pthread_mutex_lock(&mutex);
	if (fork_dispo(philo) == 1)
	{
		printf("le philo a manger %d repat sur %d.\n", philo->nb_repas_manger, slack->max_eat);
		philo->eat = 1;
		philo->time_beford_die = get_time();
		pthread_mutex_unlock(&mutex);
		usleep(slack->time2eat * 1000);
		pthread_mutex_lock(&mutex);
		philo->nb_repas_manger++;
		philo->fork = 0;
		philo->next->fork = 0;
	}
	else
		;
	pthread_mutex_unlock(&mutex);
}