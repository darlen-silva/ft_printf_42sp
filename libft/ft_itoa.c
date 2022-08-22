/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 22:04:15 by dardo-na          #+#    #+#             */
/*   Updated: 2022/06/19 22:04:20 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	digits_count(size_t n)
{
	unsigned int	digits;

	if (n == 0)
		return (1);
	digits = 0;
	while (n > 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char			*result;
	unsigned int	sign;
	long int		num;
	unsigned int	digits;

	sign = (n < 0);
	num = n;
	if (sign == 1)
		num = -num;
	digits = digits_count(num);
	result = (char *)malloc(digits + sign + 1);
	if (result == NULL)
		return (NULL);
	if (sign == 1)
		result[0] = '-';
	result[digits + sign] = '\0';
	while (digits > 0)
	{
		result[(digits - 1) + sign] = (num % 10) + '0';
		num /= 10;
		digits--;
	}
	return (result);
}
