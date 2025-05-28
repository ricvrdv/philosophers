#include "philo.h"

int	parse_args(t_table *table, char **args)
{
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
	return (0);
}