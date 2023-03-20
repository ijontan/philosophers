/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:00:51 by itan              #+#    #+#             */
/*   Updated: 2023/03/21 02:43:55 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
