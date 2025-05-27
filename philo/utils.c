#include "philo.h"

// print_error()	ft_atol()

void	print_error(const char *message)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, "\033[1;31mError: \033[0m", 18);
	while (message[i])
		i++;
	write(STDERR_FILENO, message, i);
}

static long	convert_digits(const char *str, int sign)
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
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

long    ft_atol(const char *str)
{
    int     i;
    int     sign;

    i = 0;
    sign = 1;
    if (!str)
        return (0);
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    return (sign * convert_digits(str + i, sign));
}