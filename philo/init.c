/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:05:41 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/05/29 15:06:04 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// init_structs()
// init_forks()
// init_philos()

int	init_structs(t_table *table)
{
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->simul_fail = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->nbr_philos);
	if (!table->philos)
		return (-1);
	memset(table->philos, 0, sizeof(t_philo) * table->nbr_philos);
	table->forks = safe_malloc(sizeof(t_fork) * table->nbr_philos);
	if (!table->forks)
		return (free(table->philos), -1);
	memset(table->forks, 0, sizeof(t_fork) * table->nbr_philos);
	if (safe_mutex(&table->table_mutex, INIT) == -1)
		return (free(table->philos), free(table->forks), -1);
	if (init_forks(table) == -1)
		return (-1);
	init_philos(table);
	return (0);
}

int	init_forks(t_table *table)
{
	int	i;
	int	j;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (safe_mutex(&table->forks[i].fork, INIT) == -1)
		{
			j = 0;
			while (j < i)
			{
				if (safe_mutex(&table->forks[j].fork, DESTROY) == -1)
					return (-1);
				j++;
			}
			if (safe_mutex(&table->table_mutex, DESTROY) == -1)
				return (-1);
			return (free(table->forks), free(table->philos), -1);
		}
		table->forks[i].fork_id = i;
		i++;
	}
	return (0);
}

void	init_philos(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->nbr_philos)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->full = false;
		philo->meal_count = 0;
		philo->table = table;
		philo->first_fork = &table->forks[(i + 1) % table->nbr_philos];
		philo->second_fork = &table->forks[i];
		if (philo->id % 2 == 0)
		{
			philo->first_fork = &table->forks[i];
			philo->second_fork = &table->forks[(i + 1) % table->nbr_philos];
		}
		i++;
	}
}
