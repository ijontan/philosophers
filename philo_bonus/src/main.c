/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:00:51 by itan              #+#    #+#             */
/*   Updated: 2023/03/21 01:51:42 by itan             ###   ########.fr       */
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

void	detroy_philo_data(t_philo_data *data)
{
	sem_close(data->forks);
	sem_close(data->all_shall_stop);
	sem_close(data->check_all_eaten);
	free(data->pids);
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

void	destroy_philos(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		sem_close(data->philos[i].read);
		i++;
	}
	free(data->philos);
}

int	create_child(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		data->pids[i] = fork();
		if (data->pids[i] == 0)
			child_process(&data->philos[i]);
		i++;
	}
	return (0);
}

void	kill_all_child(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		kill(data->pids[i], SIGKILL);
		sem_close(data->philos[i].read);
		i++;
	}
}

int	main(int ac, char const **av)
{
	t_philo_data	data;
	pthread_t		check_all_eaten_thread;

	if (ac != 5 && ac != 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	validate_input(ac, (char **)av);
	init_philo_data(&data, ac, av);
	if (data.max_eat_count != -1)
	{
		pthread_create(&check_all_eaten_thread, NULL, check_all_eaten, &data);
		pthread_detach(check_all_eaten_thread);
	}
	init_philos(&data);
	create_child(&data);
	sem_wait(data.all_shall_stop);
	kill_all_child(&data);
	destroy_philos(&data);
	detroy_philo_data(&data);
	return (0);
}
