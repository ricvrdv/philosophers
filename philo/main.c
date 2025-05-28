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
  char    **parsed_args;

  if (argc == 5 || argc == 6)
  {
    if (parse_args(&table, argv) == -1)
    {
      print_error("Arguments must be positive numbers\n");
      return (1);
    }
    if (init_structs(&table) == -1)
      return (1);
    // START SIMULATION TODO
    // FREE MEMORY      TODO
  }
  else
  	print_error("Run the program with 4 or 5 arguments\n");
  return (0);
}
