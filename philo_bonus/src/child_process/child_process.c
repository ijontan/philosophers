/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:08:22 by itan              #+#    #+#             */
/*   Updated: 2023/03/21 02:15:47 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	dining(t_philo *philo)
{
	sem_wait(philo->data->forks);
	philo_take_fork(philo);
	sem_wait(philo->data->forks);
	philo_take_another_fork(philo);
	gettimeofday(&philo->last_eat, NULL);
	philo_eat(philo);
	sem_wait(philo->read);
	philo->eat_count++;
	sem_post(philo->read);
	usleep(philo->data->eat_ms * 1000);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	child_process(t_philo *philo_initial)
{
	t_philo		philo;
	pthread_t	monitor_dead_thread;

	philo = *philo_initial;
	free(philo.data->pids);
	free(philo.data->philos);
	pthread_create(&monitor_dead_thread, NULL, monitor_dead, &philo);
	pthread_detach(monitor_dead_thread);
	if (philo.id % 2 == 0)
		usleep(philo.data->sleep_ms * 1000);
	while (1)
	{
		dining(&philo);
		philo_sleep(&philo);
		usleep(philo.data->sleep_ms * 1000);
		philo_think(&philo);
	}
}
