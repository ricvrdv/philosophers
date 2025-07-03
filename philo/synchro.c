/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:02:38 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/07/03 20:02:42 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// wait_all_threads()
// all_threads_running()
// count_running()
// desynchronize_philos()

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

int	all_threads_running(t_mutex *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = 0;
	pthread_mutex_lock(mutex);
	if (*threads == philo_nbr)
		ret = 1;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	count_running(t_mutex *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

void	desynchronize_philos(t_philo *philo)
{
	if (philo->table->nbr_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(30000, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}
