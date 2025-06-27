/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:59:45 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/06/26 15:59:48 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// monitor_dinner()

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;
	long	last_meal_time;

	if (get_bool(&philo->philo_mutex, &philo->full) == 1)
		return (false);
	last_meal_time = get_long(&philo->philo_mutex, &philo->last_meal_time);
	elapsed = gettime(MILLISECOND) - last_meal_time;
	time_to_die = philo->table->time_to_die;
	if (elapsed >= time_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, &table->threads_running,
			table->nbr_philos))
		;
	while (!simulation_finished(table))
	{
		i = 0;
		while (i < table->nbr_philos && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i);
			}
			i++;
		}
		precise_usleep(1000, table);
	}
	return (NULL);
}
