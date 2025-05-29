#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

# define RED "\033[1;31m"
# define RESET "\033[0m;"

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}			t_fork;

typedef struct s_philo
{
	int			id;
	long		meal_count;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_thread	thread_id;
	t_table		*table;
}				t_philo;

struct s_table
{
	long	nbr_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	long	start_simulation;
	bool	end_simulation;
	t_fork	*forks;
	t_philo	*philos;
};

// PARSE.C
int		parse_args(t_table *table, char **args);

// INIT.C
int		init_structs(t_table *table);
int		init_forks(t_table *table);
void	init_philos(t_table *table);

// START.C
int		start_simulation(t_table *table);
void	*dinner_simulation(void *data);

// UTILS.C
void	print_error(const char *message);
long	ft_atol(const char *str);

// SAFE.C
void	*safe_malloc(size_t bytes);

#endif
