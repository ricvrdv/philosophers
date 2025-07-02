/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:01:13 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/07/01 14:38:01 by applecore        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// print_error()
// ft_atol()
// gettime()
// precise_usleep()

void	print_error(const char *message)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, R"Error: "DEF, 18);
	while (message[i])
		i++;
	write(STDERR_FILENO, message, i);
}

static long	convert_digits(const char *str)
{
	long	result;
	int		digit;
	int		i;

	i = 0;
	result = 0;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (result > (LONG_MAX - digit) / 10)
			return (-1);
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

long	ft_atol(const char *str)
{
	int		i;
	long	number;

	i = 0;
	if (*str == '\0')
		return (-1);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (-1);
	number = convert_digits(str + i);
	if (number == 0)
		return (-1);
	return (number);
}

long	gettime(t_time time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		print_error("gettimeofday failed\n");
		return (-1);
	}
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
	{
		print_error("wrong input to gettime\n");
		return (-1);
	}
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 1000000);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}
