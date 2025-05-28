#include "philo.h"

// init_structs()
// init_forks()
// init_philos()

int	init_structs(t_table *table)
{
	table->end_simulation = false;
	table->forks = malloc(sizeof(t_fork) * table->nbr_philos);
	if (!table->forks)
	{
		print_error("Failed to allocate forks\n");
		return (-1);
	}
	memset(table->forks, 0, sizeof(t_fork) * table->nbr_philos);
	table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
	if (!table->philos)
	{
		free(table->forks);
		print_error("Failed to allocate philos\n");
		return (-1);
	}
	memset(table->philos, 0, sizeof(t_philo) * table->nbr_philos);
	if (init_forks(table) == -1)
		return (-1);
	init_philos(table);
	return (0);
}

int	init_forks(t_table *table)
{
	int	i;
	int	j;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&table->forks[j].fork);
				j++;
			}
			free(table->forks);
			free(table->philos);
			print_error("Failed mutex init\n");
			return (-1);
		}
		table->forks[i].fork_id = i;
		i++;
	}
	return (0);
}

void	init_philos(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->nbr_philos)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->full = false;
		philo->meal_count = 0;
		philo->table = table;
		philo->first_fork = &table->forks[(i + 1) % table->nbr_philos];
		philo->second_fork = &table->forks[i];
		if (philo->id % 2 == 0)
		{
			philo->first_fork = &table->forks[i];
			philo->second_fork = &table->forks[(i + 1) % table->nbr_philos];
		}
		i++;
	}
}
