/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:25:08 by dardo-na          #+#    #+#             */
/*   Updated: 2022/08/09 07:15:36 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_ptr_adr(char *word)
{
	char	*temp_w;

	temp_w = ft_mod_strdup(word);
	free(word);
	if (temp_w[0] == '0' && ft_strlen(temp_w) == 1)
		word = ft_mod_strdup("(nil)");
	else
	{
		word = ft_mod_strdup("0x");
		word = ft_mod_strjoin(word, temp_w);
	}
	free(temp_w);
	return (word);
}

static char	*unsigneds_flags(const char *s, unsigned long long n)
{
	char	*word;
	int		i;

	i = 1;
	word = NULL;
	if (s[i] == 'x' || s[i] == 'X')
	{
		word = ft_i_to_hex((unsigned int)n);
		if (s[i] == 'X')
		{
			i = 0;
			while (word[i++])
				word[i - 1] = ft_toupper(word[i - 1]);
		}
	}
	else if (s[i] == 'p')
	{
		word = ft_i_to_hex(n);
		word = ft_ptr_adr(word);
	}
	else if (s[i] == 'u')
		word = ft_u_to_a((unsigned int)n);
	return (word);
}

static int	ft_printchar(va_list args, char c)
{
	if (c == '%' || c == 'c')
	{
		if (c == '%')
			ft_putchar_fd('%', 1);
		else
			ft_putchar_fd(va_arg(args, int), 1);
		return (1);
	}
	return (0);
}

static int	ft_atow(const char *s, va_list args)
{
	int		i;
	char	*word;

	i = 1;
	if (ft_printchar(args, s[i]) == 1)
		return (1);
	if (s[i] == 's')
	{
		word = NULL;
		word = va_arg(args, char *);
		if (!word)
			word = ft_strdup("(null)");
		else
			word = ft_strdup(word);
	}
	if (s[i] == 'd' || s[i] == 'i')
		word = ft_itoa(va_arg(args, int));
	if (s[i] == 'x' || s[i] == 'X' || s[i] == 'p' || s[i] == 'u')
		word = unsigneds_flags(s, va_arg(args, unsigned long long));
	ft_putstr_fd(word, 1);
	i = ft_strlen(word);
	free(word);
	return (i);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		size;

	i = 0;
	size = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			size += ft_atow(&s[i], args) - 1;
			i++;
		}
		else
			ft_putchar_fd(s[i], 1);
		size++;
		i++;
	}
	va_end(args);
	return (size);
}
