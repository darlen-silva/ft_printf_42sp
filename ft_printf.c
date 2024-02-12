/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:25:08 by dardo-na          #+#    #+#             */
/*   Updated: 2024/02/12 00:55:51 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>

#define NUMS_UPPERCASE "0123456789ABCDEF"
#define NUMS_LOWERCASE "0123456789abcdef"
#define BASE10 10
#define BASE16 16

int	format_str(const char *s, va_list arg);

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

int	print_num(unsigned long num, int base, const char* nums)
{
	int			count;

	if (num == 0 || nums == NULL)
		return (0);
	count = print_num(num / base, base, nums) + 1;
	write(1, &nums[num % base], 1);
	return (count);
}

int	handle_unsigned(unsigned long num, int c)
{
	unsigned int	cast;

	cast = (unsigned int)num;
	if (cast == 0)
		return (write(1, "0", 1));
	else if (c == 'u')
		return (print_num(cast, BASE10, NUMS_LOWERCASE));
	else if (c == 'X')
		return (print_num(cast, BASE16, NUMS_UPPERCASE));
	return (print_num(cast, BASE16, NUMS_LOWERCASE));
}

int	handle_signed(long num)
{
	if (num == 0)
		return (write(1, "0", 1));
	if (num < 0)
		return (write(1, "-", 1) + print_num(-num, BASE10, NUMS_LOWERCASE));
	return (print_num(num, BASE10, NUMS_LOWERCASE));
}

int handle_addresses(void *addr)
{
	unsigned long cast;

	if (addr == NULL)
		return (write(1, "(nil)", 5));
	cast = (unsigned long)addr;
	return (write(1, "0x", 2) + print_num(cast, BASE16, NUMS_LOWERCASE));
}

int	handle_str(const char *s)
{
	int	i;

	i = 0;
	if (NULL == s)
		return (write(1, "(null)", 6));
	while(s[i])
		write(1, &s[i++], 1);
	return (i);
}

int	format_str(const char *s, va_list arg)
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
	if (*s == 'd' || *s == 'i' )
		return (handle_signed(va_arg(arg, int)));
	else if (*s == 'u' || *s == 'x' || *s == 'X')
		return (handle_unsigned(va_arg(arg, unsigned long), *s));
	else if (*s == 'p')
		return (handle_addresses(va_arg(arg, void *)));
	return (0);
}


// int main(void)
// {
// 	// int m = 2147483647;
// 	// char *h = NULL;
// 	// char c = 'A';
// 	// char *p = &c;
// 	// printf("%i\n", m+10);
// 	// int n = -123;
// 	ft_printf(" -> %d\n", ft_printf(" %% "));
// 	// print_num(n, 10);
// 	printf(" -> %d\n", printf(" %% "));
// 	return (0);
// }
