/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:18:42 by itan              #+#    #+#             */
/*   Updated: 2023/03/19 18:12:39 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*dst;

	if (size && count >= SIZE_MAX / size)
		return (0);
	total_size = count * size;
	dst = malloc(total_size);
	if (!dst)
		return (0);
	return (ft_bzero(dst, total_size));
}
