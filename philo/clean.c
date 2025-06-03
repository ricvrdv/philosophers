#include "philo.h"

void	cleanup(t_table *table)
{
	if (table->error_stage >= THREADS_JOINED)
		for (int i = 0; i < table->nbr_philos; i++)
			pthread_join(table->philos[i].thread_id, NULL);

	if (table->error_stage >= THREADS_STARTED)
		for (int i = 0; i < table->nbr_philos; i++)
			pthread_cancel(table->philos[i].thread_id);

	if (table->error_stage >= MUTEXES_INITIALIZED)
	{
		for (int i = 0; i < table->nbr_philos; i++)
			pthread_mutex_destroy(&table->forks[i].fork);
		pthread_mutex_destroy(&table->table_mutex);
	}

	if (table->error_stage >= FORKS_ALLOCATED)
		free(table->forks);

	if (table->error_stage >= PHILOS_ALLOCATED)
		free(table->philos);
}
