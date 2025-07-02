/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:04:37 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/05/29 15:05:12 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_input(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == ' ')
				j++;
			if (args[i][j] < '0' || args[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_args(t_table *table, char **args)
{
	if (!validate_input(args))
		return (-1);
	table->nbr_philos = ft_atol(args[1]);
	if (table->nbr_philos == -1)
		return (-1);
	table->time_to_die = ft_atol(args[2]);
	if (table->time_to_die == -1)
		return (-1);
	table->time_to_eat = ft_atol(args[3]);
	if (table->time_to_eat == -1)
		return (-1);
	table->time_to_sleep = ft_atol(args[4]);
	if (table->time_to_sleep == -1)
		return (-1);
	if (args[5])
	{
		table->nbr_limit_meals = ft_atol(args[5]);
		if (table->nbr_limit_meals == -1)
			return (-1);
	}
	else
		table->nbr_limit_meals = -1;
	return (0);
}
