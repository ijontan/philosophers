/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:59:27 by itan              #+#    #+#             */
/*   Updated: 2023/03/18 17:23:46 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char const **av)
{
	int				i;
	t_philo_data	data;

	if (ac != 5)
		return (1);
	data.num_of_philo = ft_atoi(av[1]);
	data.die_time_ms = ft_atoi(av[2]);
	data.eat_ms = ft_atoi(av[3]);
	data.sleep_ms = ft_atoi(av[4]);
	data.thread = ft_calloc(data.num_of_philo, sizeof(pthread_t));
	data.forks = ft_calloc(data.num_of_philo, sizeof(pthread_mutex_t));
	data.philos = ft_calloc(data.num_of_philo, sizeof(t_philo));
	data.someone_died = false;
	pthread_mutex_init(&data.print, NULL);
	pthread_mutex_init(&data.m_someone_died, NULL);
	gettimeofday(&data.start_time, NULL);
	i = 0;
	while (i < data.num_of_philo)
	{
		data.philos[i].id = i;
		data.philos[i].data = &data;
		data.philos[i].eat_count = 0;
		data.philos[i].is_dead = false;
		gettimeofday(&data.philos[i].last_eat, NULL);
		pthread_mutex_init(&data.philos[i].read_dead, NULL);
		ft_printf("philo %d: %p\n", data.philos[i].id, &data.philos[i]);
		i++;
	}
	i = 0;
	while (i < data.num_of_philo)
		pthread_mutex_init(&data.forks[i++], NULL);
	i = 0;
	while (i < data.num_of_philo)
	{
		pthread_create(&data.thread[i], NULL, routine, &data.philos[i]);
		i++;
	}
	pthread_mutex_lock(&data.m_someone_died);
	while (data.someone_died)
	{
		i = 0;
		while (i < data.num_of_philo)
		{
			pthread_mutex_lock(&data.philos[i].read_dead);
			if (data.philos[i].is_dead)
			{
				data.someone_died = true;
				pthread_mutex_unlock(&data.philos[i].read_dead);
				break ;
			}
			pthread_mutex_unlock(&data.philos[i].read_dead);
			i++;
		}
		pthread_mutex_unlock(&data.m_someone_died);
		usleep(1000);
		pthread_mutex_lock(&data.m_someone_died);
	}
	pthread_mutex_unlock(&data.m_someone_died);
	i = 0;
	while (i < data.num_of_philo)
	{
		pthread_join(data.thread[i++], NULL);
		pthread_mutex_destroy(&data.philos[i].read_dead);
	}
	i = 0;
	while (i < data.num_of_philo)
		pthread_mutex_destroy(&data.forks[i++]);
	pthread_mutex_destroy(&data.print);
	pthread_mutex_destroy(&data.m_someone_died);
	i = 0;
	free(data.thread);
	free(data.forks);
	free(data.philos);
	return (0);
}
