/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:59:27 by itan              #+#    #+#             */
/*   Updated: 2023/03/17 22:07:35 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *val)
{
	struct timeval	*a;
	t_philo			*data;

	data = (t_philo *)val;
	pthread_mutex_lock(&(data->mutex));
	a = malloc(sizeof(struct timeval));
	gettimeofday(a, NULL);
	ft_printf("ok: %i:%i\n", a->tv_usec, a->tv_sec);
	pthread_mutex_unlock(&(data->mutex));
	free(a);
	return (NULL);
}

int	main(int ac, char const **av)
{
	int		i;
	t_philo	data;

	if (ac != 2)
		return (1);
	data.num_of_philo = ft_atoi(av[1]);
	data.thread = (pthread_t *)calloc(data.num_of_philo, sizeof(pthread_t));
	gettimeofday(&data.start_time, NULL);
	pthread_mutex_init(&(data.mutex), NULL);
	i = 0;
	while (i++ < data.num_of_philo)
	{
		pthread_create(&data.thread[i], NULL, routine, &data);
	}
	i = 0;
	while (i++ < data.num_of_philo)
	{
		pthread_join(data.thread[i], NULL);
	}
	pthread_mutex_destroy(&(data.mutex));
	free(data.thread);
	return (0);
}
