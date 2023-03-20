/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:54:46 by itan              #+#    #+#             */
/*   Updated: 2023/03/20 21:50:31 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_any_dead(void *arg)
{
	t_philo_data	*data;
	int				i;
	struct timeval	current_time;

	data = (t_philo_data *)arg;
	i = 0;
	while (i < data->num_of_philo)
	{
		sem_wait(data->philos[i].read);
		gettimeofday(&current_time, NULL);
		if (get_time_diff(data->philos[i].last_eat,
							current_time) > data->die_time_ms)
		{
			philo_dead(&data->philos[i]);
			kill_all_child(data->pids, data->num_of_philo);
		}
		sem_post(data->philos[i].read);
		i++;
	}
	return (NULL);
}

void	*monitor_dead(void *arg)
{
	t_philo	*philo;

	return (NULL);
}

void	*monitor_all_finished_eating(void *arg)
{
	(void)arg;
	return (NULL);
}
