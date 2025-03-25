/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:00:04 by jmafueni          #+#    #+#             */
/*   Updated: 2025/03/20 13:11:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	arg_is_num(char *av)
{
	int	i;

	i = 0;
	while ((av[i] >= 9 && av[i] <= 13) || av[i] == 32)
			i++;
	if ((av[i]) == '+' && av[i + 1] != '\0')
		i++;
	if (av[i] == '-')
		return (0);
	if (!is_digit(av[i]))
		return (0);
	while (av[i])
	{
		if (!is_digit(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	valid_arg(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		ft_error("ERROR: Wrong input\n"
			"Usage: <number_of_philo>"
			" <time_to_die> <time_to_eat> <time_to_sleep>");
	i = 1;
	while (i < ac)
	{
		if (ft_atol(av[i]) <= 0)
			ft_error("ERROR: All arguments must be positive numbers !");
		if (!arg_is_num(av[i]))
			ft_error("Error: Only digit characers !");
		i++;
	}
	return (1);
}
