#include "philo.h"

// parse_input()
// init_forks()
// init_philos()

int	init_structs(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = false;
	table->forks = malloc(sizeof(t_fork) * table->nbr_philos);
	if (!table->forks)
	{
		print_error("Failed to allocate forks\n");
		return (-1);
	}
	table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
	if (!table->philos)
	{
		free(table->forks);
		print_error("Failed to allocate philos\n");
		return (-1);
	}
	while (i < table->nbr_philos)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
		{
			print_error("Failed mutex init\n");
			return (-1);
		}
		table->forks[i].fork_id = i;
		i++;
	}
	return (0);
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