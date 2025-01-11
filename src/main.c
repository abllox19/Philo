
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

void* philo_setup(void* arg)
{
    t_list *slack = (t_list*)arg;
	t_slack *philo = slack->philo;
    int i = slack->philo_id;

    printf("philo nb  = %d.\n", slack->philo_id);
    while (i > 1)
    {
        philo = philo->next;
        i--;
    }
    printf("bonjour je suis le philo nb %d.\n", philo->philo_id);
    while (1)
    {
        if (philo->eat == 0 && philo->nb_repas_manger < slack->max_eat)
        {
            pthread_mutex_lock(&mutex);
            philo->eat = 1;
            pthread_mutex_unlock(&mutex);
            usleep(slack->time2eat);
            pthread_mutex_lock(&mutex);
            philo->nb_repas_manger++;
            pthread_mutex_unlock(&mutex);
        }
        else if (philo->sleep == 0)
        {
            pthread_mutex_lock(&mutex);
            philo->sleep = 1;
            pthread_mutex_unlock(&mutex);
            usleep(slack->time2sleep);
        }
        else if (philo->think == 0)
        {
            pthread_mutex_lock(&mutex);
            philo->think = 1;
            pthread_mutex_unlock(&mutex);
        }
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
        sleep(1);
    }
    return NULL;
}

void* directeur(void* arg)
{
    t_list *slack = (t_list*)arg;
    pthread_t *thread;
    int i = slack->philo_nb;

    slack->philo_id = i;
    thread = malloc((sizeof (pthread_t)) * slack->philo_nb);
    while (i > 0)
    {
        if (pthread_mutex_init(&mutex, NULL) != 0)
        {
            printf("Erreur : échec d'initialisation du mutex\n");
            return NULL;
        }
        printf("lancement des philo\n");
        if (pthread_create(&thread[i], NULL, philo_setup, slack) != 0)
        {
            printf("Erreur : impossible de créer le thread 1\n");
            return NULL;
        }
        i--;
        slack->philo_id--;
    }
    // pthread_join(thread[i], NULL);
    // pthread_mutex_destroy(&mutex);
    // printf("tout les philo on manger.\n");
    // exit(1);
    return NULL;
}

void* surveillent(void* arg)
{
    t_list *slack = (t_list*)arg;
	t_slack *philo = slack->philo;
    struct  timeval time;
    long int i;

    while (1)
    {
        if (gettimeofday(&time, NULL) != 0)
            perror("gettimeofday failed");
        i = time.tv_sec;
        if ((i - philo->time_beford_die) >= slack->time2die)
        {
            printf("a %ld sec, le philo nb %d est mort.\n", i - slack->time, philo->philo_id);
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
		philo = philo->next;
        usleep(10);
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
    pthread_join(thread1, NULL);// a securiser
    pthread_join(thread2, NULL);// a securiser
    pthread_mutex_destroy(&mutex);
    printf("Tous les threads sont terminés.\n");
    return 0;
}
