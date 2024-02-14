/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:25:08 by dardo-na          #+#    #+#             */
/*   Updated: 2024/02/13 21:50:00 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	format_str(const char *s, va_list arg, int *i);

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		size;

	if (NULL == s)
		return (-1);
	i = 0;
	size = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
			size += format_str(&s[++i], args, &i);
		else
			size += write(1, &s[i], 1);
		i++;
	}
	va_end(args);
	return (size);
}

static int	handle_pointer(void *addr)
{
	unsigned long	cast;

	if (addr == NULL)
		return (write(1, "(nil)", 5));
	cast = (unsigned long)addr;
	return (write(1, "0x", 2) + print_num(cast, BASE16, NUMS_LOWERCASE));
}

static int	handle_str(t_fmt *fmt, const char *s)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (NULL == s)
		return (write(1, "(null)", 6));
	while (s[i])
		i++;
	if (fmt->flag == '.')
	{
		if (fmt->width < i)
			return (write(1, s, fmt->width));
		return (write(1, s, i));
	}
	if (fmt->right_pad)
		size += pad(i, fmt->width, ' ');
	size += write(1, s, i);
	return (size);
}

static int	handle_char(int c)
{
	return (write(1, &c, 1));
}

static int	format_str(const char *s, va_list arg, int *i)
{
	int		size;
	t_fmt	fmt;
	va_list	copy;

	*i += set_fmt(s, &fmt);
	size = 0;
	va_copy(copy, arg);
	if (fmt.spec == '%')
		size += (write(1, "%", 1));
	if (fmt.right_pad)
		size += handle_right_pad(&fmt, copy);
	if (fmt.spec == 'c')
		size += handle_char(va_arg(arg, int));
	if (fmt.spec == 's')
		size += (handle_str(&fmt, va_arg(arg, char *)));
	if (fmt.spec == 'd' || fmt.spec == 'i' )
		size += (handle_signed(&fmt, va_arg(arg, int)));
	if (fmt.spec == 'u' || fmt.spec == 'x' || fmt.spec == 'X')
		size += (handle_unsigned(va_arg(arg, unsigned long), fmt.spec));
	if (fmt.spec == 'p')
		size += (handle_pointer(va_arg(arg, void *)));
	if (fmt.left_pad)
		size += pad(size, fmt.width, ' ');
	return (size);
}
