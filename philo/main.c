/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:00:54 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/07/03 20:00:56 by rjesus-d         ###   ########.fr       */
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
		print_error("Arguments must be integers and positive\n");
		return (1);
	}
	if (init_structs(&table) == -1)
		return (1);
	if (start_simulation(&table) == -1)
		return (1);
	cleanup_dinner(&table);
	return (0);
}
