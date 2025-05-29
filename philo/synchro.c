/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:37:57 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/05/29 16:37:59 by rjesus-d         ###   ########.fr       */
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
