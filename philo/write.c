#include "philo.h"

int write_status(t_status status, t_philo *philo)
{
    long    timestamp;

    timestamp = gettime(MILLISECOND) - philo->table->start_simulation;
    if (philo->full)
        return (1);
    if (safe_mutex(&philo->table->write_mutex, LOCK) == -1)
        return (-1);
    if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
            && !simulation_finished(philo->table))
        printf("%ld\t"GREEN"%d"RESET" has taken a fork\n", timestamp, philo->id);
    else if (status == EATING && !simulation_finished(philo->table))
        printf("%ld\t"GREEN"%d"RESET" is "GREEN"eating"RESET"\n", timestamp, philo->id);
    else if (status == SLEEPING && !simulation_finished(philo->table))
        printf("%ld\t"GREEN"%d"RESET" is "GREEN"sleeping"RESET"\n", timestamp, philo->id);
    else if (status == THINKING && !simulation_finished(philo->table))
        printf("%ld\t"GREEN"%d"RESET" is "GREEN"thinking"RESET"\n", timestamp, philo->id);
    else if (status == DIED)
        printf("%ld\t"GREEN"%d"RED" died"RESET"\n", timestamp, philo->id);
    if (safe_mutex(&philo->table->write_mutex, UNLOCK) == -1)
        return (-1);
    return (0);
}