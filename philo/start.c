/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:02:20 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/07/03 20:02:23 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// start_simulation()
// dinner_simulation()
// lone_philo()

static int	start_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (safe_thread(&table->philos[i].thread_id,
				dinner_simulation, &table->philos[i], CREATE) == -1)
		{
			table->threads_started = i;
			return (-1);
		}
		i++;
	}
	table->threads_started = table->nbr_philos;
	return (0);
}

static void	join_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	table->threads_joined = true;
}

int	start_simulation(t_table *table)
{
	if (table->nbr_limit_meals == 0)
		return (0);
	if (table->nbr_philos == 1)
	{
		if (safe_thread(&table->philos[0].thread_id,
				lone_philo, &table->philos[0], CREATE) == -1)
			return (cleanup_init(table), -1);
	}
	else if (start_philo_threads(table) == -1)
		return (cleanup_dinner(table), -1);
	if (safe_thread(&table->monitor, monitor_dinner, table, CREATE) == -1)
		return (cleanup_dinner(table), -1);
	table->start_simulation = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	join_philo_threads(table);
	if (simulation_finished(table)
		|| get_bool(&table->table_mutex, &table->simul_fail))
		return (cleanup_dinner(table), -1);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	if (safe_thread(&table->monitor, NULL, NULL, JOIN) == -1)
		return (cleanup_dinner(table), -1);
	return (0);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	count_running(&philo->table->table_mutex, &philo->table->threads_running);
	desynchronize_philos(philo);
	while (!simulation_finished(philo->table) && !philo->full)
	{
		eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep * 1e3, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

void	*lone_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	count_running(&philo->table->table_mutex, &philo->table->threads_running);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}
