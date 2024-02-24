/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fmt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:42:18 by dardo-na          #+#    #+#             */
/*   Updated: 2024/02/24 17:58:48 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define FLAGS "-0. #+"
#define SPECS "csdiuxXp%"

static bool	has_char(const char *s, int c)
{
	if (s == NULL || *s == 0)
		return (false);
	return (*s == c || has_char(s + 1, c));
}

static int	get_num(const char *s, int *n, t_fmt *fmt)
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

static void	fmt_init(t_fmt *fmt)
{
	fmt->width = 0;
	fmt->prec_width = 0;
	fmt->left_width = 0;
	fmt->right_pad = false;
	fmt->left_pad = false;
	fmt->hash = false;
	fmt->plus = false;
	fmt->space = false;
	fmt->flag = 0;
	fmt->spec = 0;
	fmt->prec = 0;
}

static int	fmt_aux(const char *s, t_fmt *fmt)
{
	if (*s == '-')
	{
		fmt->left_pad = true;
		return (get_num(s, &fmt->left_width, fmt));
	}
	if (*s == '0' || *s == '.')
	{
		if (fmt->prec == '0' && *s == '.')
			fmt->width = fmt->prec_width;
		if (fmt->prec == '.' && *s == '0')
			return (0);
		fmt->prec = *s;
		return (get_num(s, &fmt->prec_width, fmt));
	}
	return (0);
}

int	set_fmt(const char *s, t_fmt *fmt)
{
	int	w;

	w = -1;
	fmt_init(fmt);
	while (s[++w] && !has_char(SPECS, s[w]))
	{
		if (s[w] == '#')
			fmt->hash = true;
		if (s[w] == '+')
			fmt->plus = true;
		if (s[w] == ' ')
			fmt->space = true;
		if (s[w] == '-' || s[w] == '0' || s[w] == '.')
		{
			w += fmt_aux(&s[w], fmt);
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
