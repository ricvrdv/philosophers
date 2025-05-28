#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*mem;

	mem = malloc(bytes);
	if (!mem)
		print_error("Failed to allocate memory\n");
	return (mem);
}