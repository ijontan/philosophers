/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 02:41:26 by itan              #+#    #+#             */
/*   Updated: 2023/03/21 02:42:15 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philo_data(t_philo_data *data, int ac, char const **av)
{
	data->num_of_philo = ft_atoi(av[1]);
	data->die_time_ms = ft_atoi(av[2]);
	data->eat_ms = ft_atoi(av[3]);
	data->sleep_ms = ft_atoi(av[4]);
	if (ac == 6)
		data->max_eat_count = ft_atoi(av[5]);
	else
		data->max_eat_count = -1;
	data->pids = ft_calloc(data->num_of_philo, sizeof(pid_t));
	sem_unlink("forks");
	sem_unlink("all_shall_stop");
	sem_unlink("check_all_eaten");
	data->forks = sem_open("forks", O_CREAT, 0644, data->num_of_philo);
	data->all_shall_stop = sem_open("all_shall_stop", O_CREAT, 0644, 1);
	data->check_all_eaten = sem_open("check_all_eaten", O_CREAT, 0644, 1);
	gettimeofday(&data->start_time, NULL);
	sem_wait(data->all_shall_stop);
}

void	init_philos(t_philo_data *data)
{
	int		i;
	char	*name;
	char	*id;

	data->philos = ft_calloc(data->num_of_philo, sizeof(t_philo));
	i = 0;
	while (i < data->num_of_philo)
	{
		id = ft_itoa(i + 1);
		name = ft_strjoin("read", id);
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat = data->start_time;
		sem_unlink(name);
		data->philos[i].read = sem_open(name, O_CREAT, 0644, 1);
		free(id);
		free(name);
		i++;
	}
}
