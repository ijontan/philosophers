/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:00:01 by itan              #+#    #+#             */
/*   Updated: 2023/03/17 18:59:56 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "libft.h"
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				sleep_ms;
	int				eat_ms;
	int				think_ms;
	int				num_of_philo;
	struct timeval	start_time;
	pthread_t		*thread;
	pthread_mutex_t	mutex;
}					t_philo;

#endif