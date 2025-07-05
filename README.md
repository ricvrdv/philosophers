# 42 - PHILOSOPHERS

<p align="center">
  <img src="https://github.com/ricvrdv/philosophers/blob/main/philo_simul.gif" alt="Dinner Simulation"
</p>

### SUMMARY

A concurrency simulation of the classic [Dining Philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) using POSIX threads in C. Each philosopher alternates between thinking, eating, and sleeping, all while sharing limited forks (resources) without encountering deadlocks or starvation.

This project implements a multi-threaded simulation where philosophers must share forks (mutexes) while attempting to eat. The simulation handles edge cases such as:
- Odd/even philosopher counts
- Time-sensitive starvation checks
- Desynchronization to avoid resource contention
- Optional meal count to end simulation gracefully

### REPOSITORY STRUCTURE
- `philo`: Contains `Makefile`, the header file `philo.h` and the source code for the program.
- `README.md`: Project overview and usage instructions.
  
### KEY FEATURES
🔁 **Threaded simulation** of philosophers using `pthread`.

⏱️ **Precise timing control** with custom `precise_usleep()`

🧑‍⚕️ **Monitor thread** to check philosopher death without busy-waiting

🔒 **Mutex-based fork access** ensuring no deadlocks

🍴 **Desynchronization logic** for concurrent start handling

🚫 **Lone philosopher logic** for handling single thread case

⚰️ **Death detection** with millisecond precision

✅ **Clean memory management** and mutex destruction

### USAGE
1. **Compile the program inside `philo` directory**
```bash
make
```

2. **Run the program with 5 or 6 arguments:**
```bash
./philo 4 410 200 200
```
```bash
./philo 5 800 300 100 10
```
The different arguments are `number_of_philos`, `time_to_die` (in ms), `time_to_eat` (in ms), `time_to_sleep` (in ms) and `number_of_times_each_philosopher_must_eat`, respectively. The last argument is optional.

The program prints a proper error message when the program is run with no arguments, with an incorrect number of arguments or with non-numeric arguments.

----
<p align="center">
  <img src="https://github.com/ricvrdv/philosophers/blob/main/dining_philosophers_diagram.png"
</p>

----
🐸 Feel free to fork, clone, or contact me for questions or feedback. 



