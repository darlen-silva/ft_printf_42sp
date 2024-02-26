/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:32:59 by dardo-na          #+#    #+#             */
/*   Updated: 2024/02/24 18:10:14 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_num(unsigned long num, int base, const char *nums)
{
	int	count;

	if (num == 0 || nums == NULL)
		return (0);
	count = print_num(num / base, base, nums);
	return (count + write(1, &nums[num % base], 1));
}

int	pad(int s, int e, int c)
{
	if (s >= e)
		return (0);
	return (write(1, &c, 1) + pad(s + 1, e, c));
}

int	num_len(unsigned long num, int base)
{
	if (num == 0)
		return (0);
	return (num_len(num / base, base) + 1);
}

int	handle_unsigned(t_fmt *fmt, unsigned long num, int c)
{
	unsigned int	cast;

	cast = (unsigned int)num;
	if (cast == 0 && !fmt->right_pad)
		return (write(1, "0", 1));
	else if (c == 'u')
		return (print_num(cast, BASE10, NUMS_LOWERCASE));
	else if (c == 'X')
		return (print_num(cast, BASE16, NUMS_UPPERCASE));
	return (print_num(cast, BASE16, NUMS_LOWERCASE));
}

int	handle_signed(t_fmt *fmt, long num)
{
	if (fmt->right_pad && num <= 0)
		return (print_num(-num, BASE10, NUMS_LOWERCASE));
	if (num == 0)
		return (write(1, "0", 1));
	if (num < 0)
		return (write(1, "-", 1) + print_num(-num, BASE10, NUMS_LOWERCASE));
	return (print_num(num, BASE10, NUMS_LOWERCASE));
}
