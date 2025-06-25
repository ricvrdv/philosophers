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
        printf("%ld\t"C"%d"DEF" has taken a fork\n", timestamp, philo->id);
    else if (status == EATING && !simulation_finished(philo->table))
        printf("%ld\t"C"%d"DEF" is "G"eating"DEF"\n", timestamp, philo->id);
    else if (status == SLEEPING && !simulation_finished(philo->table))
        printf("%ld\t"C"%d"DEF" is "P"sleeping"DEF"\n", timestamp, philo->id);
    else if (status == THINKING && !simulation_finished(philo->table))
        printf("%ld\t"C"%d"DEF" is "Y"thinking"DEF"\n", timestamp, philo->id);
    else if (status == DIED)
        printf("%ld\t"C"%d"R" died"DEF"\n", timestamp, philo->id);
    if (safe_mutex(&philo->table->write_mutex, UNLOCK) == -1)
        return (-1);
    return (0);
}