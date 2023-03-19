/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 23:28:56 by itan              #+#    #+#             */
/*   Updated: 2023/03/19 14:33:25 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_data_init(t_philo_data *data, int ac, char const **av)
{
	if (ac == 6)
		data->max_eat_count = ft_atoi(av[5]);
	else
		data->max_eat_count = -1;
	data->num_of_philo = ft_atoi(av[1]);
	data->die_time_ms = ft_atoi(av[2]);
	data->eat_ms = ft_atoi(av[3]);
	data->sleep_ms = ft_atoi(av[4]);
	data->thread = ft_calloc(data->num_of_philo, sizeof(pthread_t));
	data->forks = ft_calloc(data->num_of_philo, sizeof(pthread_mutex_t));
	data->philos = ft_calloc(data->num_of_philo, sizeof(t_philo));
	data->all_shall_stop = false;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->read_all_shall_stop, NULL);
}

void	create_philosophers(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].eat_count = 0;
		data->philos[i].is_dead = false;
		pthread_mutex_init(&data->philos[i].read_eat_count, NULL);
		pthread_mutex_init(&data->philos[i].read_last_eat, NULL);
		pthread_mutex_init(&data->philos[i].read_dead, NULL);
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	create_threads(t_philo_data *data)
{
	int	i;

	i = 0;
	gettimeofday(&data->start_time, NULL);
	while (i < data->num_of_philo)
	{
		data->philos[i].last_eat = data->start_time;
		pthread_create(&data->thread[i], NULL, routine, &data->philos[i]);
		i++;
	}
}
