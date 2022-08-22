/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:23:22 by dardo-na          #+#    #+#             */
/*   Updated: 2022/08/13 14:28:26 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_mod_atoi(const char *nptr)
{
	int	sign;
	int	save;
	int	i;

	i = 0;
	sign = 1;
	while (nptr[i] && ft_isdigit(nptr[i]) == 0)
	{
		if (nptr[i] == '-')
		{
			sign = -1;
			i++;
		}
		i++;
	}
	save = 0;
	if (ft_isdigit(nptr[i]) > 0)
	{
		while (ft_isdigit(nptr[i]) > 0)
		{
			save = (save * 10) + (nptr[i] - '0');
			i++;
		}
	}
	return (save * sign);
}
