/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:35:39 by asoumare          #+#    #+#             */
/*   Updated: 2025/01/15 00:13:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_slack *create_philosophers(int philo_nb)
{
    t_slack *head = NULL;
    t_slack *current = NULL;
    struct  timeval time;
	int i = 1;

    if (gettimeofday(&time, NULL) != 0)
        perror("gettimeofday failed");
    printf("temps = %ld\n",  time.tv_sec);
    while (i <= philo_nb)
    {
        t_slack *new_node = (t_slack *)malloc(sizeof(t_slack));
        if (!new_node)
        {
            ft_free_philosophers(head);
            return NULL;
        }    
        struct timeval time;
        gettimeofday(&time, NULL);
        long seconds = time.tv_sec;
        long milliseconds = time.tv_usec / 1000;
        new_node->philo_id = i;
        new_node->time_beford_die = seconds * 1000 + milliseconds + 1000;
        new_node->nb_repas_manger = 0;
        new_node->sleep = 0;
        new_node->eat = 0;
        new_node->fork = 0;
        new_node->think = 0;
        new_node->next = NULL;

        if (!head)
            head = new_node;
        else
            current->next = new_node;
        current = new_node;
		i++;
    }
    if (current)
        current->next = head;
    return head;
}

void init(t_list **slack, char **av, int i)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    long milliseconds = time.tv_usec / 1000;
    long seconds = time.tv_sec;
    if (!av || !slack)
        return;
    *slack = (t_list *)malloc(sizeof(t_list));
    if (!*slack)
        return;
    (*slack)->philo_nb = atoi(av[1]);
    (*slack)->time2die = atoi(av[2]);
    (*slack)->time2eat = atoi(av[3]);
    (*slack)->time2sleep = atoi(av[4]);
    (*slack)->time = seconds * 1000 + milliseconds + 1000;
    (*slack)->max_eat = (i == 1) ? atoi(av[5]) : -1;
    (*slack)->philo = create_philosophers((*slack)->philo_nb);
    if (!(*slack)->philo)
    {
        free(*slack);
        *slack = NULL;
    }
}
