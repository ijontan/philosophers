/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:59:27 by itan              #+#    #+#             */
/*   Updated: 2023/03/18 04:03:03 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_dead(t_philo *philo)
{
	if (philo->is_dead)
		return (true);
	if (get_time_diff(philo->last_eat,
						philo->current_time) > philo->data->die_time_ms)
	{
		philo->is_dead = true;
		philo_dead(philo);
		return (true);
	}
	return (false);
}

bool	check_all(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (check_dead(&data->philos[i]))
			return (true);
		i++;
	}
	return (false);
}

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
	gettimeofday(&data.start_time, NULL);
	i = 0;
	while (i < data.num_of_philo)
	{
		data.philos[i].id = i;
		data.philos[i].data = &data;
		data.philos[i].eat_count = 0;
		data.philos[i].is_dead = false;
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
	while (check_all(&data) == false)
	{
		usleep(10);
	}
	data.someone_died = true;
	i = 0;
	while (i < data.num_of_philo)
		pthread_join(data.thread[i++], NULL);
	i = 0;
	while (i < data.num_of_philo)
		pthread_mutex_destroy(&data.forks[i++]);
	i = 0;
	free(data.thread);
	free(data.forks);
	free(data.philos);
	return (0);
}
