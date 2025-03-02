/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoumare <asoumare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:22:33 by asoumare          #+#    #+#             */
/*   Updated: 2025/01/29 21:59:12 by asoumare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

pthread_mutex_t mutex;

int	fork_dispo(t_slack *philo)
{
	if (philo->fork == 0 && philo->next->fork == 0)
	{
		philo->fork = 1;
		philo->next->fork = 1;
		printf("le philo nb %d a pris la fourchettes de gauche.\n",philo->philo_id);
		printf("le philo nb %d a pris la fourchettes de droite.\n", philo->philo_id);
		return (1);
	}
	return (0);
}

void	*philo_setup(void *arg)
{
	t_list		*slack;
	t_slack		*philo;
	long int	i;

	slack = (t_list *)arg;
	philo = slack->philo;
	i = slack->philo_id;
	while (i > 1)
	{
		philo = philo->next;
		i--;
	}
	while (1)
	{
		if (philo->eat == 0 && philo->nb_repas_manger < slack->max_eat)
			eat(mutex, philo, slack);
		else if (philo->sleep == 0)
			sleepee(mutex, philo, slack);
		else if (philo->think == 0)
			think(mutex, philo);
		else if (philo->eat == 2 && philo->sleep == 2)
		{
			pthread_mutex_lock(&mutex);
			philo->think = 0;
			philo->sleep = 0;
			philo->eat = 0;
			pthread_mutex_unlock(&mutex);
		}
		if (philo->nb_repas_manger >= slack->max_eat)
			break ;
		usleep(100);
	}
	return (NULL);
}

void	*directeur(void *arg)
{
	t_list		*slack;
	pthread_t	*thread;
	int			i;

	slack = (t_list *)arg;
	slack->philo_id = 1;
	i = slack->philo_nb;
	i--;
	thread = malloc((sizeof(pthread_t)) * slack->philo_nb);
	while (i >= 0)
	{
		if (pthread_mutex_init(&mutex, NULL) != 0)
		{
			printf("Erreur : échec d'initialisation du mutex\n");
			return (NULL);
		}
		printf("lancement du philo nb %d\n", slack->philo_id);
		if (pthread_create(&thread[i], NULL, philo_setup, slack) != 0)
		{
			printf("Erreur : impossible de créer le thread %d\n", slack->philo_id);
			return (NULL);
		}
		i--;
		slack->philo_id++;
		usleep(100);
	}
	i = 0;
	// while (thread[i])
	// pthread_join(thread[i++], NULL);
	// pthread_mutex_destroy(&mutex);
	return (NULL);
}

void	surveillent(t_list *slack)
{
	t_slack		*philo;
	long int	i;
	int			j;

	j = 0;
	philo = slack->philo;
	while (1)
	{
		i = get_time();
		if ((i - philo->time_beford_die) >= slack->time2die)
		{
			printf("a %ld sec, le philo nb %d est mort.\n", i - slack->time, philo->philo_id);
			printf("temps de i %ld sec, temps du philo %ld diff des deux %ld\n", i, philo->time_beford_die, philo->time_beford_die - i);
			ft_free_list(slack);
		}
		if (philo->eat == 1)
		{
			printf("a %ld sec, le philo nb %d est en train de manger.\n", i - slack->time, philo->philo_id);
			pthread_mutex_lock(&mutex);
			philo->eat = 2;
			pthread_mutex_unlock(&mutex);
		}
		else if (philo->sleep == 1)
		{
			printf("a %ld sec, le philo nb %d est en train de dormir.\n", i - slack->time, philo->philo_id);
			pthread_mutex_lock(&mutex);
			philo->sleep = 2;
			pthread_mutex_unlock(&mutex);
		}
		else if (philo->think == 1)
		{
			printf("a %ld sec, le philo nb %d est en train de penser.\n", i - slack->time, philo->philo_id);
			pthread_mutex_lock(&mutex);
			philo->think = 2;
			pthread_mutex_unlock(&mutex);
		}
		if (philo->nb_repas_manger >= slack->max_eat)
		{
			j = philo->philo_id;
			philo = philo->next;
			while (philo->philo_id != j)
			{
				if (philo->nb_repas_manger >= slack->max_eat)
					philo = philo->next;
				else
					break ;
			}
			if (philo->philo_id == j)
			{
				printf("Tous les philo on manger.\n");
				ft_free_list(slack);
			}
		}
		philo = philo->next;
		usleep(100);
	}
	return ;
}

int	main(int ac, char **av)
{
	t_list	*slack;
	t_slack	*philo;
	int		i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (0);
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
			return (printf("Erreur : argument invalide\n"));
		i++;
	}
	if (ac == 6)
		i = 1;
	init(&slack, av, i);
	philo = slack->philo;
	printf("%d -> %ld -> %d -> %d -> %d -> %ld\n", slack->philo_nb, slack->time2die, slack->time2eat, slack->time2sleep, slack->max_eat, slack->time);
	while (philo)
	{
		printf("%d -> %d -> %ld\n", philo->philo_id, philo->nb_repas_manger, philo->time_beford_die);
		philo = philo->next;
		if (philo == slack->philo)
			break ;
	}
	printf("Début des threads\n");
	directeur(slack);
	surveillent(slack);
	return (0);
}
