/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoumare <asoumare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:26:45 by asoumare          #+#    #+#             */
/*   Updated: 2025/01/06 18:46:36 by asoumare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H

# define MINITALK_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>

typedef struct s_list
{
    int philo_id;
	int philo_nb;
    int time2die;
    int time2eat;
    int time2sleep;
    int max_eat;
    int fork_id;
	struct s_list	*next;
}					t_list;

int	ft_isdigit(char *c);
void init(t_list **slack, char **av, int i);


#endif