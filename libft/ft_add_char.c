/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:27:17 by dardo-na          #+#    #+#             */
/*   Updated: 2022/08/13 14:27:50 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_add_char(char *s, char c)
{
	char	*new_s;
	int		size;
	int		i;

	if (c == '\0')
		return (s);
	i = 0;
	size = ft_strlen(s);
	new_s = (char *)malloc((size + 2) * sizeof(char));
	while (s[i])
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = c;
	new_s[i + 1] = '\0';
	free(s);
	return (new_s);
}
