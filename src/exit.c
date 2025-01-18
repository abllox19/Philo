/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoumare <asoumare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:55:24 by asoumare          #+#    #+#             */
/*   Updated: 2025/01/18 00:39:54 by asoumare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void ft_free_philosophers(t_slack *philo)
{
    if (!philo)
        return;
    t_slack *current = philo;
    t_slack *next;
    while (current)
    {
        next = current->next;
        free(current);
        if (next == philo)
            break;
        current = next;
    }
}

void ft_free_list(t_list *slack)
{
    if (!slack)
        exit (1);
    if (slack->philo)
        ft_free_philosophers(slack->philo);
    free(slack);
    printf("fin du programme.\n");
    exit (1);
}
