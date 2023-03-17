/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 03:09:09 by itan              #+#    #+#             */
/*   Updated: 2023/03/18 04:01:49 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%07li:%i has died, he's been a great philosopher ",
			get_time_diff(philo->data->start_time, philo->current_time),
			philo->id);
	printf("and he will always be in our heart.\n");
	pthread_mutex_unlock(&(philo->data->print));
}
