/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:00:52 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/05/29 15:00:57 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo 1 2 3 4 [5]
// 1. number_of_philosophers (= number of forks)
// 2. time_to_die (in ms)
// 3. time_to_eat (in ms)
// 4. time_to_sleep (in ms)
// 5. number_of_times_each_philosopher_must_eat

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(table));
	//table.error_stage = NO_INIT;
	if (argc == 5 || argc == 6)
	{
		if (parse_args(&table, argv) == -1)
		{
			print_error("Arguments must be positive numbers\n");
			return (1);
		}
		if (init_structs(&table) == -1)
		{
			//cleanup(&table);
			return (1);
		}
		if (start_simulation(&table) == -1)
		{
			//cleanup(&table);
			return (1);
		}
	}
	else
		print_error("Incorrect number of arguments\n");
	return (0);
}
