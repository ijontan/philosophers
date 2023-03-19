/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:51:12 by itan              #+#    #+#             */
/*   Updated: 2023/03/19 14:51:12 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_dead(t_philo *philo)
{
	bool	all_shall_stop;
	bool	died;

	pthread_mutex_lock(&philo->data->read_all_shall_stop);
	all_shall_stop = philo->data->all_shall_stop;
	pthread_mutex_unlock(&philo->data->read_all_shall_stop);
	if (all_shall_stop)
		return (true);
	pthread_mutex_lock(&philo->read_dead);
	died = philo->is_dead;
	pthread_mutex_unlock(&philo->read_dead);
	if (died)
		return (true);
	return (false);
}
