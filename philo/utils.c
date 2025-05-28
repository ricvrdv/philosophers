#include "philo.h"

// print_error()
// ft_atol()

void	print_error(const char *message)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, RED"Error: "RESET, 18);
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
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (result > (LONG_MAX - digit) / 10)
			return (LONG_MAX);
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

long    ft_atol(const char *str)
{
    int     i;

    i = 0;
    if (!str)
        return (-1);
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        i++;
    if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (-1);
    return (convert_digits(str + i));
}