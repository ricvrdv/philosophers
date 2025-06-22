/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:07:07 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/06/22 19:37:28 by applecore        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <errno.h>

# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define RESET	"\033[0m"

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_status;

typedef enum e_code
{
	CREATE,
	JOIN,
	DETACH,
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
}	t_code;

typedef enum e_time
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time;

typedef enum e_stage
{
	NO_INIT,
	PHILOS_ALLOCATED,
	FORKS_ALLOCATED,
	MTX_INITIALIZED,
	THREADS_STARTED,
	THREADS_JOINED,
}	t_stage;

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
	int			philos_initialized;
	long		meal_count;
	long		last_meal_time;
	bool		full;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_thread	thread_id;
	t_table		*table;
	t_mutex		philo_mutex;
}				t_philo;

struct s_table
{
	int			forks_initialized;
	long		nbr_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	long		threads_running;
	bool		end_simulation;
	bool		all_threads_ready;
	bool		simul_fail;
	bool		ready_table_mtx;
	bool		ready_write_mtx;
	t_thread	monitor;
	t_mutex		table_mutex;
	t_mutex		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
	t_stage		error_stage;
};

// PARSE.C
int		parse_args(t_table *table, char **args);

// INIT.C
int		init_structs(t_table *table);
int		init_forks(t_table *table);
int		init_philos(t_table *table);

// START.C
int		start_simulation(t_table *table);
void	*dinner_simulation(void *data);
int		eat(t_philo *philo);
int		thinking(t_philo *philo, bool pre_simulation);
void	*lone_philo(void *data);

// GET_AND_SET.C
int		set_bool(t_mutex *mutex, bool *dest, bool value);
int		get_bool(t_mutex *mutex, bool *value);
int		set_long(t_mutex *mutex, long *dest, long value);
long	get_long(t_mutex *mutex, long *value);
int		simulation_finished(t_table *table);

// SYNCHRO.C
int		wait_all_threads(t_table *table);
int		all_threads_running(t_mutex *mutex, long *threads, long philo_nbr);
int		count_running(t_mutex *mutex, long *value);
void	desynchronize_philos(t_philo *philo);

// MONITOR.C
void	*monitor_dinner(void * data);

// WRITE.C
int		write_status(t_status status, t_philo *philo);

// UTILS.C
void	print_error(const char *message);
long	ft_atol(const char *str);
long	gettime(t_time time_code);

// SAFE.C
void	*safe_malloc(size_t bytes);
int		safe_thread(pthread_t *thread, void *(*foo)(void *), void *data,
			t_code op);
int		safe_mutex(t_mutex *mutex, t_code op);

// CLEAN.C
void	cleanup_init(t_table *table);

// DEBUG.C
void	print_table(t_table *table);
void	print_thread(t_philo *philo);

#endif
