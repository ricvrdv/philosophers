/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:06:16 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/06/23 11:50:57 by applecore        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_table *table)
{
	int	i;
	int	j;

	i = 0;
	if (table->nbr_limit_meals == 0)
		return (0);
	else if (table->nbr_philos == 1)
	{
		if (safe_thread(&table->philos[0].thread_id, lone_philo, &table->philos[0], CREATE) == -1)
			return (-1);
	}
	else
	{
		while (i < table->nbr_philos)
		{
			if (safe_thread(&table->philos[i].thread_id, dinner_simulation,
					&table->philos[i], CREATE) == -1)
			{
				//table->error_stage = THREADS_STARTED;
				j = 0;
				while (j < i)
				{
					if (safe_thread(&table->philos[j].thread_id, NULL, NULL,
							JOIN) == -1)
						return (free(table->philos), free(table->forks), -1);
					j++;
				}
				j = 0;
				while (j < table->nbr_philos)
				{
					if (safe_mutex(&table->forks[j].fork, DESTROY) == -1)
						return (free(table->philos), free(table->forks), -1);
					j++;
				}
				if (safe_mutex(&table->table_mutex, DESTROY) == -1)
					return (free(table->philos), free(table->forks), -1);
				return (free(table->philos), free(table->forks), -1);
			}
			i++;
		}
	}
	//table->error_stage = THREADS_STARTED;
	if (safe_thread(&table->monitor, monitor_dinner, table, CREATE) == -1)
		return (-1);
	table->start_simulation = gettime(MILLISECOND);
	if (set_bool(&table->table_mutex, &table->all_threads_ready, true) != 0)
		return (-1);
	i = 0;
	while (i < table->nbr_philos)
	{
		if (safe_thread(&table->philos[i].thread_id, NULL, NULL, JOIN) == -1)
		{
			//table->error_stage = THREADS_JOINED;
			return (-1);
		}
		i++;
	}
	//table->error_stage = THREADS_JOINED;
	if (simulation_finished(table)
		|| get_bool(&table->table_mutex, &table->simul_fail) == 1)
	{
		print_error("Simulation failed inside a thread\n");
		return (-1);
	}
	if (set_bool(&table->table_mutex, &table->end_simulation, true) == -1)
		return (-1);
	if (safe_thread(&table->monitor, NULL, NULL, JOIN) == -1)
		return (-1);
	return (0);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (wait_all_threads(philo->table) == -1)
	{
		set_bool(&philo->table->table_mutex, &philo->table->simul_fail, true);
		return (NULL);
	}
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	if (count_running(&philo->table->table_mutex,
			&philo->table->threads_running) == -1)
	{
		set_bool(&philo->table->table_mutex, &philo->table->simul_fail, true);
		return (NULL);
	}
	desynchronize_philos(philo);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		usleep(philo->table->time_to_sleep * 1e3); // CONVERT MILLISECONDS TO MICROSECONDS
		thinking(philo, false);
	}
	return (NULL);
}

int	eat(t_philo *philo)
{
	if (safe_mutex(&philo->first_fork->fork, LOCK) == -1)
		return (-1);
	if (write_status(TAKE_FIRST_FORK, philo) == -1)
		return (-1);
	if (safe_mutex(&philo->second_fork->fork, LOCK) == -1)
		return (-1);
	if (write_status(TAKE_SECOND_FORK, philo) == -1)
		return (-1);
	if (set_long(&philo->philo_mutex, &philo->last_meal_time,
			gettime(MILLISECOND)) == -1)
		return (-1);
	philo->meal_count++;
	if (write_status(EATING, philo) == -1)
		return (-1);
	usleep(philo->table->time_to_eat * 1e3); // CONVERT MILLISECONDS TO MICROSECONDS
	if (philo->table->nbr_limit_meals > 0
			&& philo->meal_count == philo->table->nbr_limit_meals)
	{
		if (set_bool(&philo->philo_mutex, &philo->full, true) == -1)
			return (-1);
	}
	if (safe_mutex(&philo->first_fork->fork, UNLOCK) == -1)
		return (-1);
	if (safe_mutex(&philo->second_fork->fork, UNLOCK) == -1)
		return (-1);
	return (0);
}

int	thinking(t_philo *philo, bool pre_simulation)
{
	long	time_eat;
	long	time_sleep;
	long	time_think;

	if (!pre_simulation) 
	{
		if (write_status(THINKING, philo) == -1)
			return (-1);
	}
	if (philo->table->nbr_philos % 2 == 0)
		return (0);
	time_eat = philo->table->time_to_eat;
	time_sleep = philo->table->time_to_sleep;
	time_think = time_eat * 2 - time_sleep;
	if (time_think < 0)
		time_think = 0;
	usleep(time_think * 0.42);
	return (0);
}

void	*lone_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (wait_all_threads(philo->table) == -1)
	{
		set_bool(&philo->table->table_mutex, &philo->table->simul_fail, true);
		return (NULL);
	}
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	if (count_running(&philo->table->table_mutex,
			&philo->table->threads_running) == -1)
	{
		set_bool(&philo->table->table_mutex, &philo->table->simul_fail, true);
		return (NULL);
	}
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}
