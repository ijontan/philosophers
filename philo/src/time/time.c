/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 03:46:00 by itan              #+#    #+#             */
/*   Updated: 2023/03/18 03:47:38 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time_diff(struct timeval start, struct timeval end)
{
	return ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec)
		/ 1000);
}
