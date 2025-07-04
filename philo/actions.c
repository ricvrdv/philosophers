/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:59:21 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/07/03 19:59:33 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// eat()
// thinking()

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	set_bool(&philo->philo_mutex, &philo->is_eating, true);
	philo->meal_count++;
	write_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat * 1e3, philo->table);
	set_bool(&philo->philo_mutex, &philo->is_eating, false);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meal_count == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->second_fork->fork);
	pthread_mutex_unlock(&philo->first_fork->fork);
}

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	time_eat;
	long	time_sleep;
	long	time_think;

	if (!pre_simulation)
		write_status(THINKING, philo);
	if (philo->table->nbr_philos % 2 == 0)
		return ;
	time_eat = philo->table->time_to_eat;
	time_sleep = philo->table->time_to_sleep;
	time_think = time_eat * 2 - time_sleep;
	if (time_think < 0)
		time_think = 0;
	precise_usleep(time_think * 1000 * 0.46, philo->table);
}
