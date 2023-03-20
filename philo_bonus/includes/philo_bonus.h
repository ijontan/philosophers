/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:33:34 by itan              #+#    #+#             */
/*   Updated: 2023/03/20 21:49:53 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philo_data
{
	int				sleep_ms;
	int				eat_ms;
	int				die_time_ms;
	int				max_eat_count;
	int				num_of_philo;
	sem_t			*all_shall_stop;
	sem_t			*forks;
	sem_t			*eat;
	struct timeval	start_time;
	struct s_philo	*philos;
	pid_t			*pids;
}					t_philo_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	struct timeval	last_eat;
	struct timeval	current_time;
	sem_t			*read;
	t_philo_data	*data;
}					t_philo;

bool				validate_input(int ac, char **av);
void				kill_all_child(pid_t *pids, int num);
/* -------------------------------- printing -------------------------------- */
void				philo_dead(t_philo *philo);
void				philo_take_fork(t_philo *philo);
void				philo_take_another_fork(t_philo *philo);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
/* ---------------------------------- time ---------------------------------- */
int					get_time_diff(struct timeval start, struct timeval end);
/* ---------------------------------- utils --------------------------------- */
int					ft_atoi(const char *str);
void				*ft_bzero(void *a, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isdigit(int c);
char				*ft_strchr(const char *str, int c);
char				*ft_itoa(int n);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(char *str);
size_t				ft_strlen(char const *str);
char				*ft_strjoin(char const *s1, char const *s2);
void				*ft_memcpy(void *dst, const void *src, size_t n);
#endif