/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setdown.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 00:21:10 by itan              #+#    #+#             */
/*   Updated: 2023/03/19 00:30:21 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_all(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(data->thread[i], NULL);
		pthread_mutex_destroy(&data->philos[i].read_dead);
		pthread_mutex_destroy(&data->philos[i].read_last_eat);
		pthread_mutex_destroy(&data->philos[i].read_eat_count);
		i++;
	}
}

void	destroy_all(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->m_someone_died);
	free(data->thread);
	free(data->forks);
	free(data->philos);
}
