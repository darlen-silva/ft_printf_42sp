/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:15:09 by dardo-na          #+#    #+#             */
/*   Updated: 2024/02/21 21:47:15 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <string.h>
#include <stdio.h>

#define FLAGS "-0. #+"
#define SPECS "csdiuxXp%"

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

bool	has_char(const char *s, int c)
{
	if (s == NULL || *s == 0)
		return (false);
	return (*s == c || has_char(s + 1, c));
}

int	get_num(const char *s, int *n)
{
	int	i;

	i = 0;
	if (*n > 0)
		return (0);
	while (s[0] == s[i] && !(s[i] >= '0' && s[i] <= '9'))
		i++;
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
		*n = (*n * 10) + (s[i++] - '0');
	return (i - 1);
}

int	set_fmt(const char *s, t_fmt *fmt)
{
	int	w;

	w = -1;
	memset(fmt, 0, sizeof(t_fmt));
	while (s[++w] && !has_char(SPECS, s[w]))
	{
		if (s[w] == '-')
		{
			fmt->left_pad = true;
			w += get_num(&s[w], &fmt->left_width);
			continue ;
		}
		if (s[w] == '0' || s[w] == '.')
		{
			fmt->prec = s[w];
			w += get_num(&s[w], &fmt->prec_width);
			continue ;
		}
		if (s[w] >= '1' && s[w] <= '9')
			w += get_num(&s[w], &fmt->width);
	}
	fmt->spec = s[w];
	if (fmt->width > 0)
		fmt->right_pad = true;
	// printf("(%d)\n", fmt->width);
	// printf("(%c)\n", fmt->spec);
	// printf("\n\nflag: %c\nspec: %c\nwidth: %d\nrpad: %d\nlpad: %d\nw: %d\n\n", fmt->flag, fmt->spec, fmt->width, fmt->right_pad, fmt->left_pad, w);
	return (w);
}

int	unsigneds(t_fmt *fmt, unsigned int num, int c)
{
	if (num == 0)
		return (pad(0, fmt->width - 1, c));
	if (fmt->spec == 'u')
		return (pad(num_len(num, BASE10), fmt->width, c));
	if (fmt->flag == '#' && fmt->spec == 'x' )
		return (write(1, "0x", 2));
	else if (fmt->flag == '#' && fmt->spec == 'X')
		return (write(1, "0X", 2));
	return (pad(num_len(num, BASE16), fmt->width, c));
}

int	handle_right_pad(t_fmt *fmt, va_list arg)
{
	int		size;

	size = 0;
	// printf("%d", fmt->width);
	if (fmt->spec == 'c' && fmt->width > 0 && !fmt->left_pad)
		return (pad(0, fmt->width-1, ' '));
	if (fmt->spec == 'd' || fmt->spec == 'i')
		return (0);
	if (fmt->spec == 'u' || fmt->spec == 'x' || fmt->spec == 'X')
		size += (unsigneds(fmt, va_arg(arg, unsigned long), '0'));
	return (size);
}

