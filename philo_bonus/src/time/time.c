/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 03:46:00 by itan              #+#    #+#             */
/*   Updated: 2023/03/21 02:07:05 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time_diff(struct timeval start, struct timeval end)
{
	return ((int)((end.tv_sec - start.tv_sec) * 1000) + (int)((end.tv_usec
				- start.tv_usec) / 1000));
}
