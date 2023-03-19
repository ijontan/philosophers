/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:30:17 by itan              #+#    #+#             */
/*   Updated: 2022/10/14 11:24:06 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	while (*str)
		if ((char)*(str++) == (char)c)
			return ((char *)(str - 1));
	if ((char)*(str) == (char)c)
		return ((char *)(str));
	return (0);
}