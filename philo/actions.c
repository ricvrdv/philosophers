/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:48:00 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/06/26 15:48:02 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// eat()
// thinking()

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	if (write_status(TAKE_FIRST_FORK, philo) == -1)
		return (-1);
	pthread_mutex_lock(&philo->second_fork->fork);
	if (write_status(TAKE_SECOND_FORK, philo) == -1)
		return (-1);
	if (set_long(&philo->philo_mutex, &philo->last_meal_time,
			gettime(MILLISECOND)) == -1)
		return (-1);
	if (write_status(EATING, philo) == -1)
		return (-1);
	philo->meal_count++;
	precise_usleep(philo->table->time_to_eat * 1e3, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meal_count == philo->table->nbr_limit_meals)
	{
		if (set_bool(&philo->philo_mutex, &philo->full, true) == -1)
			return (-1);
	}
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
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
	if (time_think > philo->table->time_to_die / 2)
		time_think = philo->table->time_to_die / 2;
	precise_usleep(time_think * 1000, philo->table);
	return (0);
}
