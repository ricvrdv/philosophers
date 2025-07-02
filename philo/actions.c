/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:48:00 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/07/01 17:30:56 by applecore        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// eat()
// thinking()

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meal_count++;
	write_status(EATING, philo);
	set_bool(&philo->philo_mutex, &philo->is_eating, true);
	precise_usleep(philo->table->time_to_eat * 1e3, philo->table);
	set_bool(&philo->philo_mutex, &philo->is_eating, false);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meal_count == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->second_fork->fork);
	pthread_mutex_unlock(&philo->first_fork->fork);
	return (0);
}

int	thinking(t_philo *philo, bool pre_simulation)
{
	long	time_eat;
	long	time_sleep;
	long	time_think;

	if (!pre_simulation)
		write_status(THINKING, philo);
	if (philo->table->nbr_philos % 2 == 0)
		return (0);
	time_eat = philo->table->time_to_eat;
	time_sleep = philo->table->time_to_sleep;
	time_think = time_eat * 2 - time_sleep;
	if (time_think < 0)
		time_think = 0;
	precise_usleep(time_think * 1000 * 0.46, philo->table);
	return (0);
}
