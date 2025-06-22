/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:05:41 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/06/22 19:42:14 by applecore        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// init_structs()
// init_forks()
// init_philos()

int	init_structs(t_table *table)
{
	table->philos = safe_malloc(sizeof(t_philo) * table->nbr_philos);
	if (!table->philos)
		return (-1);
	memset(table->philos, 0, sizeof(t_philo) * table->nbr_philos);
	table->forks = safe_malloc(sizeof(t_fork) * table->nbr_philos);
	if (!table->forks)
		return (cleanup_init(table), -1);
	memset(table->forks, 0, sizeof(t_fork) * table->nbr_philos);
	if (safe_mutex(&table->table_mutex, INIT) == -1)
		return (cleanup_init(table), -1);
	table->ready_table_mtx = true;
	if (safe_mutex(&table->write_mutex, INIT) == -1)
		return (cleanup_init(table), -1);
	table->ready_write_mtx = true;
	if (init_forks(table) == -1)
		return (cleanup_init(table), -1);
	if (init_philos(table) == -1)
		return (cleanup_init(table), -1);
	return (0);
}

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (safe_mutex(&table->forks[i].fork, INIT) == -1)
		{
			table->forks_initialized = i;
			return (-1);
		}
		table->forks[i].fork_id = i;
		i++;
	}
	table->forks_initialized = table->nbr_philos;
	return (0);
}

int	init_philos(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->nbr_philos)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->table = table;
		if (safe_mutex(&philo->philo_mutex, INIT) == -1)
		{
			philo->philos_initialized = i;
			return (-1);
		}
		philo->first_fork = &table->forks[(i + 1) % table->nbr_philos];
		philo->second_fork = &table->forks[i];
		if (philo->id % 2 == 0)
		{
			philo->first_fork = &table->forks[i];
			philo->second_fork = &table->forks[(i + 1) % table->nbr_philos];
		}
		i++;
	}
	philo->philos_initialized = table->nbr_philos;
	return (0);
}
