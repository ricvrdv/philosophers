/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:37:57 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/06/09 12:32:12 by applecore        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int wait_all_threads(t_table *table)
{
    int status;

    status = get_bool(&table->table_mutex, &table->all_threads_ready);
    while (status != 1)
    {
        if (status == -1)
            return (-1);
        status = get_bool(&table->table_mutex, &table->all_threads_ready);
    }
    return (status);
}

int	all_threads_running(t_mutex *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = 0;
	if (safe_mutex(mutex, LOCK) == -1)
		return (-1);
	if (*threads == philo_nbr)
		ret = 1;
	if (safe_mutex(mutex, UNLOCK) == -1)
		return (-1);
	return (ret);
}

int	count_running(t_mutex *mutex, long *value)
{
	if (safe_mutex(mutex, LOCK) == -1)
        return (-1);
    (*value)++;
    if (safe_mutex(mutex, UNLOCK) == -1)
        return (-1);
	return (0);
}
