/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:37:44 by dardo-na          #+#    #+#             */
/*   Updated: 2022/06/12 22:37:58 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	char			*str;
	unsigned int	i;

	i = 0;
	str = (char *)s;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return ((void *)str);
}
