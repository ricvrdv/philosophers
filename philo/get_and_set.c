/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:46:05 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/05/29 16:42:09 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_bool(t_mutex *mutex, bool *dest, bool value)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		print_error("Failed to lock mutex\n");
		return (-1);
	}
	*dest = value;
	if (pthread_mutex_unlock(mutex) != 0)
	{
		print_error("Failed to unlock mutex\n");
		return (-1);
	}
	return (0);
}

int	get_bool(t_mutex *mutex, bool *value)
{
	int	ret;
	
	ret = 0;
	if (pthread_mutex_lock(mutex) != 0)
	{
		print_error("Failed to lock mutex\n");
		return (-1);
	}
	if (*value)
		ret = 1;
	if (pthread_mutex_unlock(mutex) != 0)
	{
		print_error("Failed to unlock mutex\n");
		return (-1);
	}
	return (ret);
}

int	set_long(t_mutex *mutex, long *dest, long value)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		print_error("Failed to lock mutex\n");
		return (-1);
	}
	*dest = value;
	if (pthread_mutex_unlock(mutex) != 0)
	{
		print_error("Failed to unlock mutex\n");
		return (-1);
	}
	return (0);
}

long	get_long(t_mutex *mutex, long *value)
{
	long	ret;

	if (pthread_mutex_lock(mutex) != 0)
	{
		print_error("Failed to lock mutex\n");
		return (-1);
	}
	ret = *value;
	if (pthread_mutex_unlock(mutex) != 0)
	{
		print_error("Failed to unlock mutex\n");
		return (-1);
	}
	return (ret);
}

// 1 if FINISHED	0 if NOT	-1 on ERROR
int	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
