/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:07:07 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/05/29 15:07:10 by rjesus-d         ###   ########.fr       */
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
	bool	all_threads_ready;
	bool	simul_fail;
	t_mutex	table_mutex;
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

// GET_AND_SET.C
int		set_bool(t_mutex *mutex, bool *dest, bool value);
int		get_bool(t_mutex *mutex, bool *value);
int		set_long(t_mutex *mutex, long *dest, long value);
long	get_long(t_mutex *mutex, long *value);
int		simulation_finished(t_table *table);

// SYNCHRO.C
int		wait_all_threads(t_table *table);

// UTILS.C
void	print_error(const char *message);
long	ft_atol(const char *str);

// SAFE.C
void	*safe_malloc(size_t bytes);
int		safe_thread(pthread_t *thread, void *(*foo)(void *), void *data,
			t_code op);
int		safe_mutex(t_mutex *mutex, t_code op);

#endif
