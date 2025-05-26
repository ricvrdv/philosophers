#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_fork	t_fork;
typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	int			id;
	long		meal_count;
	bool		full;
	long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_thread	thread_id;
}				t_philo;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}			t_fork;

#endif
