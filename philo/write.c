/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:08:47 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/07/01 17:28:51 by applecore        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_status status, t_philo *philo)
{
	long	timestamp;
	bool	dinner_ended;

	timestamp = gettime(MILLISECOND) - philo->table->start_simulation;
	dinner_ended = simulation_finished(philo->table);
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->table->write_mutex);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !dinner_ended)
		printf("%ld\t%d has taken a fork\n", timestamp, philo->id);
	else if (status == EATING && !dinner_ended)
		printf("%ld\t%d is eating\n", timestamp, philo->id);
	else if (status == SLEEPING && !dinner_ended)
		printf("%ld\t%d is sleeping\n", timestamp, philo->id);
	else if (status == THINKING && !dinner_ended)
		printf("%ld\t%d is thinking\n", timestamp, philo->id);
	else if (status == DIED)
		printf("%ld\t%d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

/*
int	write_status(t_status status, t_philo *philo)
{
	long	timestamp;

	timestamp = gettime(MILLISECOND) - philo->table->start_simulation;
	//if (philo->full)
	//	return (1);
	if (safe_mutex(&philo->table->write_mutex, LOCK) == -1)
		return (-1);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !simulation_finished(philo->table))
		printf("%ld\t%d has taken a fork\n", timestamp, philo->id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf(G"%ld\t%d"DEF" is "G"eating"DEF"\n", timestamp, philo->id);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf("%ld\t%d is "P"sleeping"DEF"\n", timestamp, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf("%ld\t%d is "C"thinking"DEF"\n", timestamp, philo->id);
	else if (status == DIED)
		printf(R"%ld\t%d died"DEF"\n", timestamp, philo->id);
	if (safe_mutex(&philo->table->write_mutex, UNLOCK) == -1)
		return (-1);
	return (0);
}*/
