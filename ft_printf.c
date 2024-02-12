/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:25:08 by dardo-na          #+#    #+#             */
/*   Updated: 2024/02/12 10:03:15 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format_str(const char *s, va_list arg);

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
			size += format_str(&s[++i], args);
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

static int	handle_str(const char *s)
{
	int	i;

	i = 0;
	if (NULL == s)
		return (write(1, "(null)", 6));
	while (s[i])
		write(1, &s[i++], 1);
	return (i);
}

static int	format_str(const char *s, va_list arg)
{
	int	c;

	if (*s == '%')
		return (write(1, "%", 1));
	if (*s == 'c')
	{
		c = va_arg(arg, int);
		return (write(1, &c, 1));
	}
	else if (*s == 's')
		return (handle_str(va_arg(arg, char *)));
	else if (*s == 'd' || *s == 'i' )
		return (handle_signed(va_arg(arg, int)));
	else if (*s == 'u' || *s == 'x' || *s == 'X')
		return (handle_unsigned(va_arg(arg, unsigned long), *s));
	else if (*s == 'p')
		return (handle_pointer(va_arg(arg, void *)));
	return (0);
}
