#include "philo.h"

void	print_table(t_table *table)
{
	printf("nbr_of_philos =\t%lu\n", table->nbr_philos);
    printf("time_to_die =\t%lu\n", table->time_to_die);
    printf("time_to_eat =\t%lu\n", table->time_to_eat);
    printf("time_to_sleep =\t%lu\n", table->time_to_sleep);
    printf("limit_meals =\t%lu\n\n", table->nbr_limit_meals);
}

void	print_thread(t_philo *philo)
{
	printf("id =\t%d\n", philo->id);
	//printf("thread_id =\t%lu\n", philo->thread_id);
	printf("1st fork id =\t%d\n", philo->first_fork->fork_id);
	printf("2nd fork id =\t%d\n\n", philo->second_fork->fork_id);
}