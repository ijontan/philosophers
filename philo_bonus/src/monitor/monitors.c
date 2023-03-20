/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:54:46 by itan              #+#    #+#             */
/*   Updated: 2023/03/21 02:33:52 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_dead(void *arg)
{
	t_philo			*philo;
	struct timeval	current_time;
	int				time_diff;
	bool			sent_eaten;

	sent_eaten = false;
	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->read);
		gettimeofday(&current_time, NULL);
		time_diff = get_time_diff(philo->last_eat, current_time);
		if (time_diff > philo->data->die_time_ms)
		{
			philo_dead(philo);
			sem_post(philo->data->all_shall_stop);
			return (NULL);
		}
		if (philo->data->max_eat_count != -1 && !sent_eaten
			&& philo->eat_count >= philo->data->max_eat_count)
		{
			sent_eaten = true;
			sem_post(philo->data->check_all_eaten);
			return (NULL);
		}
		sem_post(philo->read);
		usleep(1000);
	}
	return (NULL);
}

void	*check_all_eaten(void *arg)
{
	t_philo_data	*data;
	int				i;

	data = (t_philo_data *)arg;
	i = 0;
	while (i < data->num_of_philo + 1)
	{
		sem_wait(data->check_all_eaten);
		i++;
	}
	sem_post(data->all_shall_stop);
	return (NULL);
}
