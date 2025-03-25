/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:13:36 by jmafueni          #+#    #+#             */
/*   Updated: 2025/03/20 13:12:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (philo->table->philo_nbr == 1)
			return (one_philo_handler(philo->table), NULL);
		if (philo->table->philo_nbr % 2)
			ft_usleep(philo->table->time_to_sleep * 0.25, philo);
		if (eat(philo) == 0)
			break ;
		if (sleep_philo(philo) == 0)
			break ;
		if (think(philo) == 0)
			break ;
	}
	return (0);
}

int	sleep_philo(t_philo *philo)
{
	print_action(philo, "is sleeping");
	return (ft_usleep(philo->table->time_to_sleep, philo));
}

int	think(t_philo *philo)
{
	if (print_action(philo, "is thinking") == true)
		return (0);
	return (1);
}

void	one_philo_handler(t_table *table)
{
	print_action(table->philo, "has taken a fork");
	usleep(table->time_to_die * 1000);
	return ;
}
