
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoumare <asoumare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:22:33 by asoumare          #+#    #+#             */
/*   Updated: 2025/01/08 21:47:28 by asoumare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

pthread_mutex_t mutex;

void* directeur(void* arg)
{
    t_list *slack = (t_list*)arg;
	t_slack *philo = slack->philo;
    int i = 10;
    while (i > 0)
    {
        pthread_mutex_lock(&mutex);
        philo->eat = 1;
        pthread_mutex_unlock(&mutex);
        philo = philo->next;
        sleep(1);

        pthread_mutex_lock(&mutex);
        philo->sleep = 1;
        pthread_mutex_unlock(&mutex);
        philo = philo->next;
        sleep(1);
        
        pthread_mutex_lock(&mutex);
        philo->think = 1;
        pthread_mutex_unlock(&mutex);
        philo = philo->next;
        sleep(1);
        i--;
    }
    return NULL;
}

void* surveillent(void* arg)
{
    t_list *slack = (t_list*)arg;
	t_slack *philo = slack->philo;
    struct  timeval time;
    int i;

    while (1)
    {
        if (gettimeofday(&time, NULL) != 0)
            perror("gettimeofday failed");
        i = time.tv_sec;
        if ((i - philo->time_beford_die) >= slack->time2die)
        {
            printf("le philo nb %d est mort.\n", philo->philo_id);
            ft_free_list(slack);
        }
        if (philo->eat == 1)
        {
            printf("le philo nb %d est en train de manger.\n", philo->philo_id);
            pthread_mutex_lock(&mutex);
            philo->eat = 2;
            pthread_mutex_unlock(&mutex);
        }
        else if (philo->sleep == 1)
        {
            printf("le philo nb %d est en train de dormir.\n", philo->philo_id);
            pthread_mutex_lock(&mutex);
            philo->sleep = 2;
            pthread_mutex_unlock(&mutex);
        }
        else if (philo->think == 1)
        {
            printf("le philo nb %d est en train de penser.\n", philo->philo_id);
            pthread_mutex_lock(&mutex);
            philo->think = 2;
            pthread_mutex_unlock(&mutex);
        }
		philo = philo->next;
        usleep(1000);
    }
    return NULL;
}

int main(int ac, char **av)
{
    t_list  *slack;
    t_slack *philo;
    int     i = 1;
    pthread_t thread1, thread2;

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
    printf("%d -> %d -> %d -> %d -> %d \n", slack->philo_nb, slack->time2die, slack->time2eat, slack->time2sleep, slack->max_eat);
    while (philo)
    {
        printf("%d -> %d -> %d\n", philo->philo_id, philo->nb_repas_manger, philo->time_beford_die);
        philo = philo->next;
        if (philo == slack->philo)
            break;
    }
    if (pthread_mutex_init(&mutex, NULL) != 0)
        return (printf("Erreur : échec d'initialisation du mutex\n"));
    printf("Début des threads\n");
    if (pthread_create(&thread1, NULL, directeur, slack) != 0)
        return (printf("Erreur : impossible de créer le thread 1\n"));
    if (pthread_create(&thread2, NULL, surveillent, slack) != 0)
        return (printf("Erreur : impossible de créer le thread 2\n"));
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&mutex);
    printf("Tous les threads sont terminés.\n");
    return 0;
}
