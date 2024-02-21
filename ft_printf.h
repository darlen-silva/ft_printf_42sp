/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 07:44:07 by dardo-na          #+#    #+#             */
/*   Updated: 2024/02/21 17:45:30 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdbool.h>

# define NUMS_UPPERCASE "0123456789ABCDEF"
# define NUMS_LOWERCASE "0123456789abcdef"
# define BASE10 10
# define BASE16 16

typedef struct s_fmt
{
	int		width;
	int		prec_width;
	bool	right_pad;
	bool	left_pad;
	char	flag;
	char	spec;
}	t_fmt;

int		ft_printf(const char *s, ...);
int		print_num(unsigned long num, int base, const char *nums);
int		handle_unsigned(unsigned long num, int c);
int		handle_signed(t_fmt *fmt, long num);
int		set_fmt(const char *s, t_fmt *fmt);
int		handle_right_pad(t_fmt *fmt, va_list arg);
int		pad(int s, int e, int c);

#endif
