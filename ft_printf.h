/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 07:44:07 by dardo-na          #+#    #+#             */
/*   Updated: 2024/02/25 22:38:49 by dardo-na         ###   ########.fr       */
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
	int		left_width;
	bool	right_pad;
	bool	left_pad;
	bool	hash;
	bool	plus;
	bool	space;
	char	flag;
	char	spec;
	char	prec;
}	t_fmt;

int		ft_printf(const char *s, ...);
int		print_num(unsigned long num, int base, const char *nums);
int		num_len(unsigned long num, int base);
int		handle_unsigned(t_fmt *fmt, unsigned long num, int c);
int		handle_signed(t_fmt *fmt, long num);
int		set_fmt(const char *s, t_fmt *fmt);
int		handle_right_pad(t_fmt *fmt, va_list arg);
int		pad(int s, int e, int c);

#endif // FT_PRINTF_H
