/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 07:44:07 by dardo-na          #+#    #+#             */
/*   Updated: 2024/02/12 10:03:27 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

# define NUMS_UPPERCASE "0123456789ABCDEF"
# define NUMS_LOWERCASE "0123456789abcdef"
# define BASE10 10
# define BASE16 16

int		ft_printf(const char *s, ...);
int		print_num(unsigned long num, int base, const char *nums);
int		handle_unsigned(unsigned long num, int c);
int		handle_signed(long num);

#endif
