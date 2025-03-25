/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:07:57 by jmafueni          #+#    #+#             */
/*   Updated: 2025/03/25 13:50:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	take_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (print_action(philo, "has taken a fork") == true)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_lock(&philo->left_fork);
	if (print_action(philo, "has taken a fork") == true)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
		return (0);
	}
	return (1);
}

int	take_forks_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	if (print_action(philo, "has taken a fork") == true)
	{
		pthread_mutex_unlock(&philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	if (print_action(philo, "has taken a fork") == true)
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	return (1);
}

int	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 != 0)
	{
		if (!take_forks_odd(philo))
			return (0);
	}
	else
	{
		if (take_forks_even(philo) == 0)
			return (0);
	}
	return (1);
}

int	eats_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	philo->nb_repas_manger++;
	if (philo->nb_repas_manger == philo->table->max_eats)
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->eat_mutex);
	return (1);
}

int	eat(t_philo *philo)
{
	if (!take_forks(philo))
		return (0);
	pthread_mutex_lock(&philo->eat_time);
	if (print_action(philo, "is eating") == true)
		return (pthread_mutex_unlock(&philo->eat_time), 0);
	philo->time_beford_die = get_time();
	pthread_mutex_unlock(&philo->eat_time);
	if (ft_usleep(philo->table->time_to_eat, philo) == 0)
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (!eats_eaten(philo))
		return (0);
	return (1);
}
