/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:19:48 by itan              #+#    #+#             */
/*   Updated: 2023/03/19 18:18:09 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	neg;

	result = 0;
	neg = 1;
	while (ft_strchr(" \n\t\v\f\r", *str))
		str++;
	if (ft_strchr("+-", *str))
		if (*(str++) == '-')
			neg = -1;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + *(str++) - '0';
	return (result * neg);
}
