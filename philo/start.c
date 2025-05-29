#include "philo.h"

int	start_simulation(t_table *table)
{
	int	i;
	int	j;

	i = 0;
	if (table->nbr_limit_meals == 0)
		return (0);
	else if (table->nbr_philos == 1)
		; // TODO
	else
	{
		while (i < table->nbr_philos)
		{
			if (pthread_create(&table->philos[i].thread_id, NULL,
					dinner_simulation, &table->philos[i]) != 0)
			{
				j = 0;
				while (j < i)
				{
					pthread_join(table->philos[j].thread_id, NULL);
					j++;
				}
				j = 0;
				while (j < table->nbr_philos)
				{
					pthread_mutex_destroy(&table->forks[j].fork);
					j++;
				}
				free(table->philos);
				free(table->forks);
				print_error("Failed to create thread\n");
				return (-1);
			}
			i++;
		}
	}
	return (0);
}

void	*dinner_simulation(void *data)
{
	//t_philo	*philo;

	//philo = (t_philo *)data;
	(void)data;
	return (NULL);
}