/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:59:27 by itan              #+#    #+#             */
/*   Updated: 2023/03/19 02:51:50 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_dead(t_philo *philo)
{
	struct timeval	current_time;
	struct timeval	last_eat;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(&philo->read_last_eat);
	last_eat = philo->last_eat;
	pthread_mutex_unlock(&philo->read_last_eat);
	if (get_time_diff(last_eat, current_time) > philo->data->die_time_ms)
	{
		pthread_mutex_lock(&philo->read_dead);
		philo->is_dead = true;
		pthread_mutex_unlock(&philo->read_dead);
		pthread_mutex_lock(&philo->data->m_someone_died);
		philo->data->all_shall_stop = true;
		pthread_mutex_unlock(&philo->data->m_someone_died);
		philo_dead(philo);
		return (true);
	}
	return (false);
}

static bool	check_eat_count(t_philo *philo)
{
	int	eat_count;

	pthread_mutex_lock(&philo->read_eat_count);
	eat_count = philo->eat_count;
	pthread_mutex_unlock(&philo->read_eat_count);
	if (eat_count == philo->data->max_eat_count)
		return (true);
	return (false);
}

static bool	stop_all(t_philo_data *data)
{
	pthread_mutex_lock(&data->m_someone_died);
	data->all_shall_stop = true;
	pthread_mutex_unlock(&data->m_someone_died);
	return (true);
}

bool	check_routine(t_philo_data *data)
{
	int	i;
	int	finished_eating;

	finished_eating = 0;
	while (1)
	{
		i = 0;
		while (i < data->num_of_philo)
		{
			if (check_dead(&data->philos[i]))
				return (true);
			if (data->max_eat_count != -1 && check_eat_count(&data->philos[i]))
				finished_eating++;
			i++;
		}
		if (finished_eating == data->num_of_philo)
			return (stop_all(data));
		finished_eating = 0;
		usleep(900);
	}
	return (false);
}

int	main(int ac, char const **av)
{
	t_philo_data	data;

	if (ac != 5 && ac != 6)
		return (1);
	philo_data_init(&data, ac, av);
	create_philosophers(&data);
	create_threads(&data);
	check_routine(&data);
	join_all(&data);
	destroy_all(&data);
	return (0);
}
