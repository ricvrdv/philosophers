#include "philo.h"

// ./philo 1 2 3 4 [5]
// 1. number_of_philosophers (= number of forks)
// 2. time_to_die (in ms)
// 3. time_to_eat (in ms)
// 4. time_to_sleep (in ms)
// 5. number_of_times_each_philosopher_must_eat

int main(int argc, char **argv)
{
  t_table table;

  if (argc == 5 || argc == 6)
  {
    if (parse_args(&table, argv) == -1)
    {
      print_error("Arguments must be 0 or positive numbers\n");
      return (1);
    }
    if (init_structs(&table) == -1)
      return (1);
    //printf("argv 1: %ld\nargv 2: %ld\nargv 3: %ld\nargv 4: %ld\nargv 5: %ld\n", table.nbr_philos, table.time_to_die, table.time_to_eat, table.time_to_sleep, table.nbr_limit_meals);
    if (start_simulation(&table) == -1)
      return (1);
    // FREE MEMORY      TODO
  }
  else
  	print_error("Run the program with 4 or 5 arguments\n");
  return (0);
}
