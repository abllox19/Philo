/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoumare <asoumare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:26:45 by asoumare          #+#    #+#             */
/*   Updated: 2025/01/28 21:16:16 by asoumare         ###   ########.fr       */
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
    long int time_beford_die;
    int eat;
    int think;
    int sleep;
    int fork;
    struct s_slack *next;
} t_slack;

typedef struct s_list
{
    pthread_mutex_t mutex;
    int philo_id;
    int philo_nb;
    long int time2die;
    int time2eat;
    int time2sleep;
    int max_eat;
    long int time;
    t_slack *philo;
} t_list;

/*      action      */

void	    eat(pthread_mutex_t mutex, t_slack *philo ,t_list *slack);
void	    sleepee(pthread_mutex_t mutex, t_slack *philo ,t_list *slack);
void	    think(pthread_mutex_t mutex, t_slack *philo);
int         fork_dispo(t_slack *philo);

/*      init        */
void        init(t_list **slack, char **av, int i);
long int    get_time(void);

/*      is digit        */
int         ft_isdigit(char *c);


/*      exit           */
void        ft_free_philosophers(t_slack *philo);
void        ft_free_list(t_list *slack);


#endif