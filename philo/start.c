/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:06:16 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/05/29 15:06:18 by rjesus-d         ###   ########.fr       */
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
			if (pthread_create(&table->philos[i].thread_id, NULL,
					dinner_simulation, &table->philos[i]) != 0)
			{
				j = 0;
				while (j < i)
				{
					pthread_join(table->philos[j].thread_id, NULL);
					j++;
				}
				j = 0;
				while (j < table->nbr_philos)
				{
					pthread_mutex_destroy(&table->forks[j].fork);
					j++;
				}
				pthread_mutex_destroy(&table->table_mutex);
				free(table->philos);
				free(table->forks);
				print_error("Failed to create thread\n");
				return (-1);
			}
			i++;
		}
	}
	if (set_bool(&table->table_mutex, &table->all_threads_ready, true) != 0)
		return (-1);
	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	if (simulation_finished(table)
		|| get_bool(&table->table_mutex, &table->simul_fail) == 1)
	{
		print_error("Simulation failed inside a thread\n");
		return (-1);
	}
	printf("\n✅ Created "GREEN"%ld"RESET" philosopher threads\n\n", table->nbr_philos);
	return (0);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf("Philosopher "GREEN"%d"RESET" thread started (ID: "GREEN"%lu"RESET" )\n", philo->id, philo->thread_id);
	if (wait_all_threads(philo->table) == -1)
	{
		set_bool(&philo->table->table_mutex, &philo->table->simul_fail, true);
		return (NULL);
	}
	return (NULL);
}
