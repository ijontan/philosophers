/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 01:20:29 by itan              #+#    #+#             */
/*   Updated: 2023/03/18 17:24:23 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_someone_died);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->m_someone_died);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->m_someone_died);
	if (philo->is_dead)
		return (true);
	if (get_time_diff(philo->last_eat,
						philo->current_time) > philo->data->die_time_ms)
	{
		pthread_mutex_lock(&philo->read_dead);
		philo->is_dead = true;
		pthread_mutex_unlock(&philo->read_dead);
		pthread_mutex_lock(&philo->data->m_someone_died);
		philo->data->someone_died = true;
		pthread_mutex_unlock(&philo->data->m_someone_died);
		philo_dead(philo);
		return (true);
	}
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
	pthread_mutex_lock(&(philo->data->forks[right_fork]));
	gettimeofday(&philo->current_time, NULL);
	if (check_dead(philo))
	{
		pthread_mutex_unlock(&(philo->data->forks[right_fork]));
		return (false);
	}
	philo_take_another_fork(philo);
	return (true);
}

void	put_fork(t_philo *philo, int right_fork, int left_fork)
{
	if (!philo->is_dead)
	{
		pthread_mutex_unlock(&(philo->data->forks[right_fork]));
		pthread_mutex_unlock(&(philo->data->forks[left_fork]));
	}
}

void	eat(t_philo *philo)
{
	gettimeofday(&philo->current_time, NULL);
	if (check_dead(philo))
		return ;
	philo->last_eat = philo->current_time;
	philo_eat(philo);
	philo->eat_count++;
	usleep(philo->data->eat_ms * 1000);
}

bool	dinning(t_philo *philo)
{
	int	right_fork;
	int	left_fork;

	right_fork = (philo->id + 1) % philo->data->num_of_philo;
	left_fork = philo->id;
	if (!get_fork(philo, right_fork, left_fork))
		return (false);
	eat(philo);
	put_fork(philo, right_fork, left_fork);
	return (true);
}

void	*routine(void *val)
{
	t_philo	*philo;

	philo = (t_philo *)val;
	if (philo->id % 2 == 1)
		usleep(philo->data->sleep_ms * 1000);
	while (1)
	{
		if (philo->data->someone_died)
			pthread_detach(philo->data->thread[philo->id]);
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
