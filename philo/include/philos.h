/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:08:59 by jmafueni          #+#    #+#             */
/*   Updated: 2025/03/20 13:07:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <limits.h>
# include <string.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				philo_id;
	int				nb_repas_manger;
	long long		time_beford_die;
	pthread_t		thread;
	pthread_mutex_t	ph_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eat_time;
	struct s_table	*table;
	struct s_philo	*next;
}					t_philo;

typedef struct s_table
{
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eats;
	int				all_alive;
	long			time;
	pthread_mutex_t	all_alive_mutex;
	pthread_mutex_t	print_mutex;
	t_philo	*philo;
}					t_table;

/*				check				*/

// const char			*check_input(const char *str);
int					check_n_handle_death(t_philo *philo);
int					check_philos(t_table *table);
int					check_total_eats(t_philo *philo);
int					check_is_dead(t_philo *philo);
int					is_digit(char c);
int					is_space(char c);
int					arg_is_num(char *av);
int					valid_arg(int ac, char **av);

/*				utils				*/

void				ft_error(const char *msg);
long				ft_atol(const char *str);
void				clean_up(t_table *table);
void				one_philo_handler(t_table *table);
long				get_time(void);

/*				init				*/

void				init_philos(t_table *table);
void				*init_table(t_table *table, int ac, char **av);
void				created_threads(t_table *table);
void				join_threads(t_table *table);
void				*philo_routine(void *arg);
void				start(t_table *table);

/*				actions				*/

bool				print_action(t_philo *philo, const char *action);
int					eat(t_philo *philo);
int					ft_usleep(int milliseconds, t_philo *philo);
int					eats_eaten(t_philo *philo);
int					sleep_philo(t_philo *philo);
int					take_forks(t_philo *philo);
int					take_forks_even(t_philo *philo);
int					take_forks_odd(t_philo *philo);
int					think(t_philo *philo);



#endif
