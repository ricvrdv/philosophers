/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:07:37 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/05/29 15:08:00 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// safe_malloc()
// safe_thread()
// safe_mutex()

void	*safe_malloc(size_t bytes)
{
	void	*mem;

	mem = malloc(bytes);
	if (!mem)
	{
		print_error("Failed to allocate memory\n");
		return (NULL);
	}
	return (mem);
}

static int	error_thread(int status, t_code op)
{
	if (status == 0)
		return (0);
	if (status == EAGAIN)
		print_error("Insufficient resources to create another thread.\n");
	else if (status == EPERM)
		print_error("No permission to set the scheduling policy and "
			"parameters specified in attr.\n");
	else if (status == EINVAL && op == CREATE)
		print_error("Invalid settings in attr.\n");
	else if (status == EINVAL && (op == JOIN || op == DETACH))
		print_error("thread is not a joinable thread.\n");
	else if (status == ESRCH)
		print_error("No thread with the ID thread could be found.\n");
	else if (status == EDEADLK)
		print_error("A deadlock was detected "
			"or thread specifies the calling thread.\n");
	return (-1);
}

int	safe_thread(pthread_t *thread, void *(*foo)(void *), void *data,
	t_code op)
{
	if (op == CREATE)
		return (error_thread(pthread_create(thread, NULL, foo, data), op));
	else if (op == JOIN)
		return (error_thread(pthread_join(*thread, NULL), op));
	else if (op == DETACH)
		return (error_thread(pthread_detach(*thread), op));
	else
		return (-1);
}

static int	error_mutex(int status, t_code op)
{
	if (status == 0)
		return (0);
	if (status == EINVAL && (op == LOCK || op == UNLOCK))
		print_error("The value specified by mutex does not refer to an "
			"initialised mutex object.\n");
	else if (status == EINVAL && op == INIT)
		print_error("The value specified by attr is invalid.\n");
	else if (status == EDEADLK)
		print_error("The current thread already owns the mutex.\n");
	else if (status == EPERM)
		print_error("The current thread does not own the mutex.\n");
	else if (status == ENOMEM)
		print_error("Insufficient memory exists to initialize the mutex.\n");
	else if (status == EBUSY)
		print_error("The mutex could not be acquired because it was "
			"already locked.\n");
	return (-1);
}

int	safe_mutex(t_mutex *mutex, t_code op)
{
	if (op == LOCK)
		return (error_mutex(pthread_mutex_lock(mutex), op));
	else if (op == UNLOCK)
		return (error_mutex(pthread_mutex_unlock(mutex), op));
	else if (op == INIT)
		return (error_mutex(pthread_mutex_init(mutex, NULL), op));
	else if (op == DESTROY)
		return (error_mutex(pthread_mutex_destroy(mutex), op));
	else
		return (-1);
}
