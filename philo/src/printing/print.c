/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:59:33 by itan              #+#    #+#             */
/*   Updated: 2023/03/18 03:50:42 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%07li %i has taken a fork\n",
			get_time_diff(philo->data->start_time, philo->current_time),
			philo->id);
	pthread_mutex_unlock(&(philo->data->print));
}

void	philo_take_another_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%07li %i has taken another fork\n",
			get_time_diff(philo->data->start_time, philo->current_time),
			philo->id);
	pthread_mutex_unlock(&(philo->data->print));
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%07li %i eating like nobody's business\n",
			get_time_diff(philo->data->start_time, philo->current_time),
			philo->id);
	pthread_mutex_unlock(&(philo->data->print));
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%07li %i is sleeping\n", get_time_diff(philo->data->start_time,
				philo->current_time), philo->id);
	pthread_mutex_unlock(&(philo->data->print));
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%07li %i is thinking\n", get_time_diff(philo->data->start_time,
				philo->current_time), philo->id);
	pthread_mutex_unlock(&(philo->data->print));
}
