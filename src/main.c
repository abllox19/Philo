/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoumare <asoumare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:22:33 by asoumare          #+#    #+#             */
/*   Updated: 2025/01/06 21:54:21 by asoumare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void* fonction_thread1(int *i)
{
    for (int b = 0; b < 5; b++) {
        i++;
        sleep(1);
    }
    return NULL;
}

// Fonction exécutée par le second thread
void* fonction_thread2(int *i)
{
    for (int b = 0; b < 5; b++) {
        printf("Thread 2 : %d\n", *i);
        sleep(1);
    }
    return NULL;
}

int main(int ac, char **av)
{
	t_list	*slack;
	t_slack *philo;
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
	philo = slack->philo;
	printf("%d -> %d -> %d -> %d -> %d \n", slack->philo_nb, slack->time2die, slack->time2eat, slack->time2sleep, slack->max_eat);
	while (philo)
	{
		printf("%d -> %d -> %d\n", philo->philo_id, philo->nb_repas_manger, philo->time_beford_die);
		philo = philo->next;
		if (philo == slack->philo)
			break;
	}
	printf("fin\n");
	pthread_t thread1, thread2;

    // Créer deux threads
	i = 0;
    pthread_create(&thread1, NULL, fonction_thread1(&i), NULL);
    pthread_create(&thread2, NULL, fonction_thread2(&i), NULL);

    // Attendre la fin des threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Tous les threads sont terminés.\n");
    return 0;
}