/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:05:43 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/06/04 17:06:46 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_table *table)
{
	pthread_mutex_destroy(&table->table_mutex);
	if (table->ready_write_mtx)
		pthread_mutex_destroy(&table->write_mutex);
}

/*
void	cleanup(t_table *table)
{
	int	i;

	if (table->error_stage >= THREADS_JOINED)
	{
		i = -1;
		while (++i < table->nbr_philos)
			pthread_join(table->philos[i].thread_id, NULL);
	}
	if (table->error_stage >= MTX_INITIALIZED)
	{
		i = -1;
		while (++i < table->nbr_philos)
			pthread_mutex_destroy(&table->forks[i].fork);
		pthread_mutex_destroy(&table->table_mutex);
	}
	if (table->error_stage >= FORKS_ALLOCATED)
	{
		free(table->forks);
		table->forks = NULL;
	}
	if (table->error_stage >= PHILOS_ALLOCATED)
	{
		free(table->philos);
		table->philos = NULL;
	}
}
*/
