/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:29:58 by jmafueni          #+#    #+#             */
/*   Updated: 2025/03/25 14:01:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (!valid_arg(ac, av))
		return (1);
	memset(&table, 0, sizeof(t_table));
	init_table(&table, ac, av);
	start(&table);
	while (1)
	{
		if (!check_philos(&table))
			break ;
		usleep(800);
	}
	join_threads(&table);
	clean_up(&table);
	return (0);
}

/*-fsanitize=thread*/
