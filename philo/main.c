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

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(table));
	if (argc != 5 && argc != 6)
	{
		print_error("Incorrect number of arguments\n");
		return (1);
	}
	if (parse_args(&table, argv) == -1)
	{
		print_error("Arguments must be numeric and positive\n");
		return (1);
	}
	if (init_structs(&table) == -1)
		return (1);
	if (start_simulation(&table) == -1)
		return (1);
	cleanup_dinner(&table);
	return (0);
}
