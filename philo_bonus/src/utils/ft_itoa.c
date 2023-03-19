/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:10:45 by itan              #+#    #+#             */
/*   Updated: 2023/03/19 21:16:25 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// int	get_n_digit(int n)
// {
// 	int	i;

// 	i = 0;
// 	n *= -1;
// 	while (n > 0)
// 	{
// 		n /= 10;
// 		i++;
// 	}
// 	return (i);
// }

// char	*ft_itoa(int n)
// {
// 	char	*dst;
// 	int		i;
// 	int		is_neg;

// 	is_neg = 0;
// 	if (n < 0)
// 		is_neg = 1;
// 	i = get_n_digit(n) + is_neg;
// 	n *= -1;
// 	dst = (char *)malloc(sizeof(char) * (i + 1));
// 	if (!dst)
// 		return (0);
// 	dst[i] = '\0';
// 	while (--i > 0)
// 	{
// 		dst[i] = n % 10 + '0';
// 		n /= 10;
// 	}
// 	if (is_neg)
// 		dst[0] = '-';
// 	return (dst);
// }

int	count_char(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*output;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	i = count_char(n);
	output = (char *)malloc(sizeof(char) * (i + 1));
	if (!output)
		return (NULL);
	output[i--] = '\0';
	if (n < 0)
	{
		output[0] = '-';
		n = -n;
	}
	while (n != 0)
	{
		output[i--] = 48 + (n % 10);
		n /= 10;
	}
	return (output);
}
