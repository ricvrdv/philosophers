/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:08:47 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/06/26 16:08:50 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_status(t_status status, t_philo *philo)
{
	long	timestamp;

	timestamp = gettime(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return (1);
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
}
