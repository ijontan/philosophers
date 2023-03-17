/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 01:20:29 by itan              #+#    #+#             */
/*   Updated: 2023/03/18 03:40:07 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_fork(t_philo *philo)
{
	int	second_fork;

	if (philo->id + 1 == philo->data->num_of_philo)
		second_fork = 0;
	else
		second_fork = philo->id + 1;
	pthread_mutex_lock(&(philo->data->forks[philo->id]));
	gettimeofday(&philo->current_time, NULL);
	philo_take_fork(philo);
	pthread_mutex_lock(&(philo->data->forks[second_fork]));
	gettimeofday(&philo->current_time, NULL);
	philo_take_another_fork(philo);
}

void	put_fork(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->data->forks[philo->id]));
	pthread_mutex_unlock(&(philo->data->forks[philo->id + 1]));
}

void	eat(t_philo *philo)
{
	gettimeofday(&philo->current_time, NULL);
	philo->last_eat = philo->current_time;
	philo_eat(philo);
	philo->eat_count++;
	usleep(philo->data->eat_ms * 1000);
}

void	dinning(t_philo *philo)
{
	get_fork(philo);
	eat(philo);
	put_fork(philo);
}

void	*routine(void *val)
{
	t_philo	*philo;

	philo = (t_philo *)val;
	if (philo->id % 2 == 1)
		usleep(philo->data->sleep_ms * 1000);
	while (!philo->is_dead)
	{
		dinning(philo);
		gettimeofday(&philo->current_time, NULL);
		philo_sleep(philo);
		usleep(philo->data->sleep_ms * 1000);
		gettimeofday(&philo->current_time, NULL);
		philo_think(philo);
	}
	if (philo->is_dead)
		pthread_detach(philo->data->thread[philo->id]);
	return (NULL);
}
