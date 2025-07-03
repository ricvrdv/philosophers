/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:01:26 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/07/03 20:01:28 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// monitor_dinner()

static bool	philo_died(t_philo *philo, long now)
{
	long	elapsed;
	long	last_meal_time;

	pthread_mutex_lock(&philo->philo_mutex);
	if (philo->full || philo->is_eating)
	{
		pthread_mutex_unlock(&philo->philo_mutex);
		return (false);
	}
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->philo_mutex);
	elapsed = now - last_meal_time;
	return (elapsed >= philo->table->time_to_die);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;
	long	now;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running, table->nbr_philos))
		usleep(100);
	while (!simulation_finished(table))
	{
		now = gettime(MILLISECOND);
		i = 0;
		while (i < table->nbr_philos && !simulation_finished(table))
		{
			if (philo_died(table->philos + i, now))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i);
			}
			i++;
		}
		usleep(10);
	}
	return (NULL);
}
