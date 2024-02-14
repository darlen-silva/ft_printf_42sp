/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:15:09 by dardo-na          #+#    #+#             */
/*   Updated: 2024/02/13 21:22:15 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

#define FLAGS "-0. #+"

int	num_len(unsigned long num, int base)
{
	if (num == 0)
		return (0);
	return (num_len(num / base, base) + 1);
}

int	pad(int s, int e, int c)
{
	if (s >= e)
		return (0);
	return (write(1, &c, 1) + pad(s + 1, e, c));
}

int	set_fmt(const char *s, t_fmt *fmt)
{
	int		w;
	char	*f;

	f = FLAGS;
	fmt->width = 0;
	fmt->left_pad = 0;
	fmt->right_pad = 0;
	fmt->flag = 0;
	w = 0;
	while (*f)
	{
		if (*f == s[w])
			fmt->flag = s[w++];
		f++;
	}
	while (s[w] >= '0' && s[w] <= '9')
		fmt->width = (fmt->width * 10) + (s[w++] - '0');
	fmt->spec = s[w];
	if (fmt->flag == '-')
		fmt->left_pad = 1;
	else
		fmt->right_pad = 1;
	// printf("(%d)\n", num_len(0, 10));
	// printf("\n\nflag: %c\nspec: %c\nwidth: %d\nrpad: %d\nlpad: %d\nw: %d\n\n", fmt->flag, fmt->spec, fmt->width, fmt->right_pad, fmt->left_pad, w);
	return (w);
}

int	unsigneds(t_fmt *fmt, unsigned int num, int c)
{
	if (num == 0)
		return (pad(0, fmt->width - 1, c));
	if (fmt->spec == 'u')
		return (pad(num_len(num, BASE10), fmt->width, c));
	return (pad(num_len(num, BASE16), fmt->width, c));
}

int	handle_right_pad(t_fmt *fmt, va_list arg)
{
	int		size;
	int		num;
	int		c;

	c = ' ';
	size = 0;
	if (fmt->flag == '0')
		c = '0';
	if (fmt->spec == 'd' || fmt->spec == 'i')
	{
		num = va_arg(arg, int);
		if (fmt->spec == 'c' || num == 0)
			return (pad(size, fmt->width - 1, c));
		if (num < 0 && (fmt->spec == 'd' || fmt->spec == 'i'))
		{
			size += write(1, "-", 1);
			num = -num;
		}
		size += pad(num_len(num, BASE10) + size, fmt->width, c);
	}
	if (fmt->spec == 'u' || fmt->spec == 'x' || fmt->spec == 'X')
	{
		unsigned int cast = va_arg(arg, unsigned long);
		if (fmt->spec == 'p')
			size += pad(num_len(cast, BASE16), fmt->width, c);
		size += (unsigneds(fmt, cast, c));
	}
	return (size);
}

