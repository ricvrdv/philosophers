/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:00:52 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/06/22 19:10:48 by applecore        ###   ########.fr       */
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
	if (argc < 5 || argc > 6)
	{
		print_error("Incorrect number of arguments\n");
		return (1);
	}
	if (parse_args(&table, argv) == -1)
	{
		print_error("Arguments must be positive numbers\n");
		return (1);
	}
	if (init_structs(&table) == -1)
		return (1);
	if (start_simulation(&table) == -1)
	{
		//cleanup(&table);
		return (1);
	}
	//cleanup(&table);
	return (0);
}
