#include "philo.h"

// init_table()

static long  get_time_in_ms(void)
{
  struct timeval	tv;
  
  if (gettimeofday(&tv, NULL) == -1)
    return (-1); 
  return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

void  init_table(t_table *table, char **args)
{
	long	timestamp;

	timestamp = get_time_in_ms();
	if (timestamp == -1)
		print_error("Failed to get current time.\n");
	table->nbr_philos = ft_atol(args[1]);
	table->time_to_die = ft_atol(args[2]);
	table->time_to_eat = ft_atol(args[3]);
	table->time_to_sleep = ft_atol(args[4]);
	table->nbr_limit_meals = ft_atol(args[5]);
	table->start_simulation = timestamp;
}