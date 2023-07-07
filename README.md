# Philosopher

## Table of Contents

- [Philosopher](#philosopher)
  - [Table of Contents](#table-of-contents)
  - [About ](#about-)
    - [Prerequisites](#prerequisites)
    - [Installing](#installing)
  - [Usage ](#usage-)
      - [parameters](#parameters)

## About <a name = "about"></a>

42 projects aims to explore ideas of concurrency in c; a modified version of the dining philosopher problem.

the mandatory is to solve it with multi-threading and mutex
the bonus is to solve it with child processes and semaphore

### Prerequisites

1. unix system
2. gcc

### Installing

clone the projects
```sh
git clone https://github.com/ijontan/philosophers.git
```

## Usage <a name = "usage"></a>

#### parameters
1. n - number of philosophers
2. t - time before a philosopher starve to death
3. e - time a philosopher takes to eat
4. s - time a philosopher sleeps after eating
5. m - least number of meals all philosopher have to eat before ending (optional)


run mandatory
```sh
cd philo && make && ./philo {n} {t} {e} {s} {m}
```
run bonus
```sh
cd philo_bonus && make && ./philo_bonus {n} {t} {e} {s} {m}
```
