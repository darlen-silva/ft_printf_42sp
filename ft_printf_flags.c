/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:15:09 by dardo-na          #+#    #+#             */
/*   Updated: 2024/02/24 18:17:21 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	unsigned_right_pad_aux(t_fmt *fmt, unsigned int num, int len)
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

static int	unsigneds(t_fmt *fmt, unsigned int num)
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

static int	signed_right_pad_aux(t_fmt *fmt, int num, int len, int sign)
{
	int	size;
	int	width;

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

static int	handle_right_signed_pad(t_fmt *fmt, long num)
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
		return (pad(0, fmt->width - 1, ' '));
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
