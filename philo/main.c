#include "philo.h"

// ./philo 1 2 3 4 [5]
// 1. number_of_philosophers (= number of forks)
// 2. time_to_die (in ms)
// 3. time_to_eat (in ms)
// 4. time_to_sleep (in ms)
// 5. number_of_times_each_philosopher_must_eat

int main(int argc, char **argv)
{
  t_table *table;

  table = malloc(sizeof(t_table));
  if (argc == 5 || argc == 6)
  {
    // PARSE ARGS				TODO
    init_table(table, argv);
    // PUT ARGS INSIDE STRUCT	TODO
    // CREATE THREADS			TODO
    // LOCK EACH FORK			TODO
  }
  else
  	print_error("Run the program with 4 or 5 arguments.\n");
  return (0);
}
