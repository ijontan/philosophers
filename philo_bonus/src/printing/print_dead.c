/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 03:09:09 by itan              #+#    #+#             */
/*   Updated: 2023/03/19 01:03:44 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_dead(t_philo *philo)
{
	gettimeofday(&philo->current_time, NULL);
	if (PRETTY)
	{
		printf("%07i %i%s has died☠️ , he's been a great philosopher ",
			get_time_diff(philo->data->start_time, philo->current_time),
			philo->id, "\033[1;31m");
		printf("and he will always be in our heart. RIP%s⚰️\n", "\033[0m");
	}
	else
		printf("%07i %i died\n",
			get_time_diff(philo->data->start_time, philo->current_time),
			philo->id);
}
