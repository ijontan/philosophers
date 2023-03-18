/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 01:20:29 by itan              #+#    #+#             */
/*   Updated: 2023/03/19 00:08:47 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_dead(t_philo *philo)
{
	bool	all_shall_stop;
	bool	died;

	pthread_mutex_lock(&philo->data->m_someone_died);
	all_shall_stop = philo->data->all_shall_stop;
	pthread_mutex_unlock(&philo->data->m_someone_died);
	if (all_shall_stop)
		return (true);
	pthread_mutex_lock(&philo->read_dead);
	died = philo->is_dead;
	pthread_mutex_unlock(&philo->read_dead);
	if (died)
		return (true);
	return (false);
}

bool	get_fork(t_philo *philo, int right_fork, int left_fork)
{
	pthread_mutex_lock(&(philo->data->forks[left_fork]));
	gettimeofday(&philo->current_time, NULL);
	if (check_dead(philo))
	{
		pthread_mutex_unlock(&(philo->data->forks[left_fork]));
		return (false);
	}
	philo_take_fork(philo);
	if (right_fork == left_fork)
		return (true);
	pthread_mutex_lock(&(philo->data->forks[right_fork]));
	gettimeofday(&philo->current_time, NULL);
	if (check_dead(philo))
	{
		pthread_mutex_unlock(&(philo->data->forks[left_fork]));
		pthread_mutex_unlock(&(philo->data->forks[right_fork]));
		return (false);
	}
	philo_take_another_fork(philo);
	return (true);
}

void	put_fork(t_philo *philo, int right_fork, int left_fork)
{
	pthread_mutex_unlock(&(philo->data->forks[right_fork]));
	pthread_mutex_unlock(&(philo->data->forks[left_fork]));
}

void	eat(t_philo *philo)
{
	gettimeofday(&philo->current_time, NULL);
	if (check_dead(philo))
		return ;
	pthread_mutex_lock(&(philo->read_last_eat));
	philo->last_eat = philo->current_time;
	pthread_mutex_unlock(&(philo->read_last_eat));
	philo_eat(philo);
	pthread_mutex_lock(&(philo->read_eat_count));
	philo->eat_count++;
	pthread_mutex_unlock(&(philo->read_eat_count));
	usleep(philo->data->eat_ms * 1000);
}

bool	dinning(t_philo *philo)
{
	int	right_fork;
	int	left_fork;

	right_fork = (philo->id) % philo->data->num_of_philo;
	left_fork = philo->id - 1;
	if (!get_fork(philo, right_fork, left_fork))
		return (false);
	if (right_fork == left_fork)
		return (true);
	eat(philo);
	put_fork(philo, right_fork, left_fork);
	return (true);
}

void	*routine(void *val)
{
	t_philo	*philo;

	philo = (t_philo *)val;
	if (philo->id % 2 == 0)
		usleep(philo->data->sleep_ms * 1000);
	while (1)
	{
		if (!dinning(philo))
			return (NULL);
		gettimeofday(&philo->current_time, NULL);
		if (check_dead(philo))
			return (NULL);
		philo_sleep(philo);
		usleep(philo->data->sleep_ms * 1000);
		gettimeofday(&philo->current_time, NULL);
		if (check_dead(philo))
			return (NULL);
		philo_think(philo);
	}
	return (NULL);
}
