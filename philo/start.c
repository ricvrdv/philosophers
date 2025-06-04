/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:06:16 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/06/04 12:37:19 by applecore        ###   ########.fr       */
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
		; // TODO
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
	printf("\n> Created "GREEN"%ld"RESET" philosopher threads\n\n", table->nbr_philos);
	return (0);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf("Philosopher "GREEN"%d"RESET" thread started (ID: "GREEN"%lu"RESET")\n", philo->id, philo->thread_id);
	if (wait_all_threads(philo->table) == -1)
	{
		set_bool(&philo->table->table_mutex, &philo->table->simul_fail, true);
		return (NULL);
	}
	//print_thread(philo);
	return (NULL);
}
