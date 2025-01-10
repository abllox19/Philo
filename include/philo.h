/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoumare <asoumare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:26:45 by asoumare          #+#    #+#             */
/*   Updated: 2025/01/10 21:08:53 by asoumare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H

# define MINITALK_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <pthread.h>
typedef struct s_slack
{
    int philo_id;
    int nb_repas_manger;
    int time_beford_die;
    int eat;
    int think;
    int sleep;
    struct s_slack *next;
} t_slack;

typedef struct s_list
{
    int philo_nb;
    int time2die;
    int time2eat;
    int time2sleep;
    int max_eat;
    t_slack *philo;
} t_list;

/*      init        */
void init(t_list **slack, char **av, int i);

/*      is digit        */
int	ft_isdigit(char *c);


/*      exit           */
void ft_free_philosophers(t_slack *philo);
void ft_free_list(t_list *slack);


#endif