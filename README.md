# 42 - PHILOSOPHERS

<p align="center">
  <img src="https://github.com/ricvrdv/philosophers/blob/main/philo_simul.gif" alt="Dinner Simulation"
</p>

### SUMMARY

### REPOSITORY STRUCTURE
- `philo`: Contains `Makefile`, the header file `philo.h` and the source code for the program.
- `README.md`: Project overview and usage instructions.
  
### KEY FEATURES

### USAGE
1. **Compile the program**
```
make
```

2. **Run the program with 5 or 6 arguments:**
```
./philo 4 410 200 200
```
```
./philo 5 800 300 100 10
```
The different arguments are `number_of_philos`, `time_to_die` (in ms), `time_to_eat` (in ms), `time_to_sleep` (in ms) and `number_of_times_each_philosopher_must_eat`, respectively. The last argument is optional.

The program prints a proper error message when the program is run with no arguments, with an incorrect number of arguments or with non-numeric arguments.



