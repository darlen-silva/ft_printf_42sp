/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:15:09 by dardo-na          #+#    #+#             */
/*   Updated: 2024/02/23 01:22:14 by dardo-na         ###   ########.fr       */
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

int	get_num(const char *s, int *n, t_fmt *fmt)
{
	int	i;

	i = 0;
	if (s == NULL || *s == 0)
		return (0);
	if (*n > 0)
		*n = 0;
	while (s[0] == s[i] && !(s[i] >= '1' && s[i] <= '9'))
		i++;
	if (s[i] == ' ')
		fmt->space = true;
	if (s[i] == '+')
		fmt->plus = true;
	while (s[i] == ' ' || s[i] == '+')
		i++;
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
		*n = (*n * 10) + (s[i++] - '0');
	if (*n == 0)
		return (0);
	return (i - 1);
}

int	set_fmt(const char *s, t_fmt *fmt)
{
	int	w;

	w = -1;
	memset(fmt, 0, sizeof(t_fmt));
	while (s[++w] && !has_char(SPECS, s[w]))
	{
		if (s[w] == '#')
			fmt->hash = true;
		if (s[w] == '+')
			fmt->plus = true;
		if (s[w] == ' ')
			fmt->space = true;
		if (s[w] == '-')
		{
			fmt->left_pad = true;
			w += get_num(&s[w], &fmt->left_width, fmt);
			continue ;
		}
		if (s[w] == '0' || s[w] == '.')
		{
			if (fmt->prec == '0' && s[w] == '.')
				fmt->width = fmt->prec_width;
			if (fmt->prec == '.' && s[w] == '0')
				continue ;
			fmt->prec = s[w];
			w += get_num(&s[w], &fmt->prec_width, fmt);
			continue ;
		}
		if (s[w] >= '1' && s[w] <= '9')
			w += get_num(&s[w], &fmt->width, fmt);
	}
	fmt->spec = s[w];
	if (fmt->width > 0 || fmt->prec || fmt->space || fmt->hash || fmt->plus)
		fmt->right_pad = true;
	return (w);
}

int	unsigned_right_pad_aux(t_fmt *fmt, unsigned int num, int len)
{
	int	size;

	size = 0;
	if (fmt->prec == '.')
	{
		if (fmt->width > 0 && fmt->prec_width <= len)
			size += pad(len, fmt->width, ' ');
		else if (fmt->width > 0 && fmt->prec_width > len)
			size += pad(fmt->prec_width, fmt->width, ' ');
	}
	if (num == 0)
		return (size + pad(0, fmt->prec_width, '0'));
	return (size + pad(len, fmt->prec_width - !num, '0'));
}

int	unsigneds(t_fmt *fmt, unsigned int num)
{
	int	len;
	int	size;

	size = 0;
	if (fmt->spec == 'u')
		len = num_len(num, BASE10);
	else
		len = num_len(num, BASE16);
	if (num == 0 && !fmt->prec)
		return (pad(0, fmt->width - 1, ' ') + write(1, "0", 1));
	if (fmt->spec == 'u' && fmt->prec)
		return (size + unsigned_right_pad_aux(fmt, num, len));
	if (fmt->hash && fmt->spec == 'x')
		size += write(1, "0x", 2);
	if (fmt->hash && fmt->spec == 'X')
		size += write(1, "0X", 2);
	if (fmt->spec == 'x' && fmt->prec)
		return (size + unsigned_right_pad_aux(fmt, num, len));
	if (fmt->spec == 'X' && fmt->prec)
		return (size + unsigned_right_pad_aux(fmt, num, len));
	return (size + pad(len, fmt->width - !num, ' '));
}

int	signed_right_pad_aux(t_fmt *fmt, int num, int len, int sign)
{
	int	size;
	int width;

	size = 0;
	if (fmt->prec == '.')
	{
		if (fmt->width > 0 && fmt->prec_width <= len)
			size += pad(len, fmt->width - sign, ' ');
		else if (fmt->width > 0 && fmt->prec_width > len)
			size += pad(fmt->prec_width, fmt->width - sign, ' ');
	}
	width = fmt->space + fmt->plus;
	if (num == 0)
		return (size + pad(width, fmt->prec_width + width, '0'));
	width = fmt->prec_width + (fmt->prec == '.') - sign;
	if (sign)
		return (size + write(1, "-", 1) + pad(len, width, '0'));
	width = fmt->prec_width - (fmt->space + fmt->plus);
	return (size + pad(len, width, '0'));
}

int	handle_right_signed_pad(t_fmt *fmt, long num)
{
	int	len;
	int	sign;
	int	size;

	size = 0;
	sign = (num < 0);
	if (sign)
		num = -num;
	len = num_len(num, BASE10);
	if (fmt->plus && !sign)
		size += write(1, "+", 1);
	if (fmt->space && !sign)
		size += write(1, " ", 1);
	if (num == 0 && !fmt->prec)
		return (size + pad(0, fmt->width - 1, ' ') + write(1, "0", 1));
	if (fmt->prec == '.' || fmt->prec == '0')
		return (size + signed_right_pad_aux(fmt, num, len, sign));
	if (sign)
		return (size + pad(len, fmt->width - 1, ' ') + write(1, "-", 1));
	return (size + pad(len, fmt->width - !num, ' '));
}

int	handle_right_pad(t_fmt *fmt, va_list arg)
{
	int		len;
	void	*p;

	if (fmt->spec == 'c' && fmt->width > 0 && !fmt->left_pad)
		return (pad(0, fmt->width-1, ' '));
	else if (fmt->spec == 'd' || fmt->spec == 'i')
		return (handle_right_signed_pad(fmt, va_arg(arg, int)));
	else if (fmt->spec == 'u' || fmt->spec == 'x' || fmt->spec == 'X')
		return (unsigneds(fmt, va_arg(arg, unsigned int)));
	else if (fmt->spec == 'p')
	{
		p = va_arg(arg, void *);
		if (p == NULL)
			return (pad(0, fmt->width - 5, ' '));
		len = num_len((unsigned long)p, BASE16);
		return (pad(len, fmt->width - 2, ' '));
	}
	else
		return (0);
}

