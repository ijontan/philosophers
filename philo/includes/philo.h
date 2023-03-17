/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:00:01 by itan              #+#    #+#             */
/*   Updated: 2023/03/18 03:57:35 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "libft.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo_data
{
	int				sleep_ms;
	int				eat_ms;
	int				die_time_ms;
	int				num_of_philo;
	bool			someone_died;
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
	struct timeval	last_eat;
	struct timeval	current_time;
	bool			is_dead;
	t_philo_data	*data;
}					t_philo;

/* ---------------------------------- print --------------------------------- */
void				philo_take_fork(t_philo *philo);
void				philo_take_another_fork(t_philo *philo);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
void				philo_dead(t_philo *philo);
/* --------------------------------- routine -------------------------------- */
void				*routine(void *val);
/* ---------------------------------- time ---------------------------------- */
long int			get_time_diff(struct timeval start, struct timeval end);

#endif