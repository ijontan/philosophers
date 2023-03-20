/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:59:33 by itan              #+#    #+#             */
/*   Updated: 2023/03/18 18:00:15 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_fork(t_philo *philo)
{
	if (PRETTY)
		printf("%07i %i%s has taken a fork%s\n",
			get_time_diff(philo->data->start_time, philo->current_time),
			philo->id, "\033[1;34m", "\033[0m");
	else
		printf("%07i %i has taken a fork\n",
			get_time_diff(philo->data->start_time, philo->current_time),
			philo->id);
}

void	philo_take_another_fork(t_philo *philo)
{
	if (PRETTY)
		printf("%07i %i%s has taken another fork%s\n",
			get_time_diff(philo->data->start_time, philo->current_time),
			philo->id, "\033[1;32m", "\033[0m");
	else
		printf("%07i %i has taken a fork\n",
			get_time_diff(philo->data->start_time, philo->current_time),
			philo->id);
}

void	philo_eat(t_philo *philo)
{
	if (PRETTY)
		printf("%07i %i%s eating like nobody's business%s🤤👍🍔\n",
			get_time_diff(philo->data->start_time, philo->current_time),
			philo->id, "\033[1;33m", "\033[0m");
	else
		printf("%07i %i is eating\n",
			get_time_diff(philo->data->start_time, philo->current_time),
			philo->id);
}

void	philo_sleep(t_philo *philo)
{
	if (PRETTY)
		printf("%07i %i%s is sleeping%s😴😴\n",
			get_time_diff(philo->data->start_time, philo->current_time),
			philo->id, "\033[1;36m", "\033[0m");
	else
		printf("%07i %i is sleeping\n",
			get_time_diff(philo->data->start_time, philo->current_time),
			philo->id);
}

void	philo_think(t_philo *philo)
{
	if (PRETTY)
	{
		printf("%07i %i%s is thinking about ",
			get_time_diff(philo->data->start_time, philo->current_time),
			philo->id, "\033[1;37m");
		printf("how his life is completely meaningless%s\n", "\033[0m");
	}
	else
		printf("%07i %i is thinking\n", get_time_diff(philo->data->start_time,
				philo->current_time), philo->id);
}
