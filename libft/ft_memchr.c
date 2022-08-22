/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 01:43:21 by dardo-na          #+#    #+#             */
/*   Updated: 2022/06/22 01:43:41 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			count;
	unsigned char	*str;
	unsigned char	aux;

	str = (unsigned char *)s;
	aux = (unsigned char)c;
	count = 0;
	while (count < n)
	{
		if (*str == aux)
			return (str);
		str++;
		count++;
	}
	return (NULL);
}
