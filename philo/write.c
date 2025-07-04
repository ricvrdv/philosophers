/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:03:11 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/07/04 20:12:07 by rjesus-d         ###   ########.fr       */
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
		printf(G"%ld\t%d"DEF" is "G"eating"DEF"\n", timestamp, philo->id);
	else if (status == SLEEPING && !dinner_ended)
		printf("%ld\t%d is "P"sleeping"DEF"\n", timestamp, philo->id);
	else if (status == THINKING && !dinner_ended)
		printf("%ld\t%d is "C"thinking"DEF"\n", timestamp, philo->id);
	else if (status == DIED)
		printf(R"%ld\t%d died"DEF"\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
