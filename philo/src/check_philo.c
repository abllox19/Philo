/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:53:15 by jmafueni          #+#    #+#             */
/*   Updated: 2025/03/25 13:53:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	check_is_dead(t_philo *philo)
{
	int	alive_status;

	pthread_mutex_lock(&philo->table->all_alive_mutex);
	alive_status = philo->table->all_alive;
	pthread_mutex_unlock(&philo->table->all_alive_mutex);
	return (alive_status);
}

int	check_n_handle_death(t_philo *philo)
{
	long	current_time;
	long	last_eat;

	pthread_mutex_lock(&philo->eat_time);
	last_eat = philo->time_beford_die;
	pthread_mutex_unlock(&philo->eat_time);
	current_time = get_time();
	if (current_time - last_eat > philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%ld %d died\n",
			current_time - philo->table->time, philo->philo_id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		pthread_mutex_lock(&philo->table->all_alive_mutex);
		philo->table->all_alive = 0;
		pthread_mutex_unlock(&philo->table->all_alive_mutex);
		return (1);
	}
	return (0);
}

int	check_total_eats(t_philo *philo)
{
	int	i;
	int	full;

	if (philo->table->max_eats < 0)
		return (0);
	i = 0;
	full = 1;
	while (i < philo->table->philo_nbr)
	{
		pthread_mutex_lock(&philo[i].eat_mutex);
		if (philo[i].nb_repas_manger < philo->table->max_eats)
			full = 0;
		pthread_mutex_unlock(&philo[i].eat_mutex);
		i++;
	}
	return (full);
}

int	check_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (check_total_eats(table->philo))
			return (0);
		if (check_n_handle_death(&table->philo[i]))
			return (0);
		i++;
	}
	return (1);
}
