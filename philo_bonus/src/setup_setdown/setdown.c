/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setdown.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 02:41:39 by itan              #+#    #+#             */
/*   Updated: 2023/03/21 02:44:10 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	detroy_philo_data(t_philo_data *data)
{
	sem_close(data->forks);
	sem_close(data->all_shall_stop);
	sem_close(data->check_all_eaten);
	free(data->pids);
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
