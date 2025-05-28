#include "philo.h"

// init_table()
// init_forks()
// init_philos()

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
		print_error("Failed to get current time\n");
	table->nbr_philos = ft_atol(args[1]);
	table->time_to_die = ft_atol(args[2]);
	table->time_to_eat = ft_atol(args[3]);
	table->time_to_sleep = ft_atol(args[4]);
	table->nbr_limit_meals = ft_atol(args[5]);
	table->start_simulation = timestamp;
	table->end_simulation = false;
	init_forks(table);
	init_philos(table);
}

void	init_forks(t_table *table)
{
	t_fork	*fork;
	int		i;

	i = 0;
	table->forks = safe_malloc(sizeof(t_fork) * table->nbr_philos);
	while (i < table->nbr_philos)
	{
		fork = &table->forks[i];
		memset(fork, 0, sizeof(t_fork));
		fork->fork_id = i;
		if (pthread_mutex_init(&fork->fork, NULL) != 0)
			print_error("Failed mutex init\n");
		i++;
	}
}

void	init_philos(t_table *table)
{
	t_philo	*philo;
	int		i;
	
	i = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->nbr_philos);
	while (i < table->nbr_philos)
	{
		philo = &table->philos[i];
		memset(philo, 0, sizeof(t_philo));
		philo->id = i + 1;
		philo->meal_count = 0;
		philo->last_meal_time = table->start_simulation; // CHECK THIS
		philo->left_fork = &table->forks[i];
		philo->right_fork = &table->forks[(i + 1) % table->nbr_philos];
		philo->thread_id = 0;
		philo->table = table;
		i++;
	}
}