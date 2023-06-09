/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:00:01 by itan              #+#    #+#             */
/*   Updated: 2023/03/19 18:17:54 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef PRETTY
#  define PRETTY 0
# endif

typedef struct s_philo_data
{
	int				sleep_ms;
	int				eat_ms;
	int				die_time_ms;
	int				max_eat_count;
	int				num_of_philo;
	bool			all_shall_stop;
	pthread_mutex_t	read_all_shall_stop;
	struct timeval	start_time;
	pthread_t		*thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	struct s_philo	*philos;
}					t_philo_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	pthread_mutex_t	read_eat_count;
	struct timeval	last_eat;
	pthread_mutex_t	read_last_eat;
	struct timeval	current_time;
	bool			is_dead;
	pthread_mutex_t	read_dead;
	t_philo_data	*data;
}					t_philo;

bool				validate_input(int ac, char **av);

/* ---------------------------------- print --------------------------------- */
void				philo_take_fork(t_philo *philo);
void				philo_take_another_fork(t_philo *philo);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
void				philo_dead(t_philo *philo);
/* --------------------------------- routine -------------------------------- */
bool				check_dead(t_philo *philo);
void				*routine(void *val);
/* ------------------------------ setup_setdown ----------------------------- */
void				philo_data_init(t_philo_data *data, int ac,
						char const **av);
void				create_philosophers(t_philo_data *data);
void				create_threads(t_philo_data *data);

void				join_all(t_philo_data *data);
void				destroy_all(t_philo_data *data);
/* ---------------------------------- time ---------------------------------- */
int					get_time_diff(struct timeval start, struct timeval end);
/* ---------------------------------- utils --------------------------------- */
int					ft_atoi(const char *str);
void				*ft_bzero(void *a, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isdigit(int c);
char				*ft_strchr(const char *str, int c);

#endif