/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardo-na <dardo-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 01:40:52 by dardo-na          #+#    #+#             */
/*   Updated: 2022/06/22 01:40:53 by dardo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordsnum(const char *s, char delimiter)
{
	size_t	words;

	words = 0;
	if (*s == '\0')
		return (words);
	if (delimiter == '\0')
		return (1);
	while (*s == delimiter && *s)
		s++;
	while (*s)
	{
		words++;
		while (*s != delimiter && *s)
			s++;
		while (*s == delimiter && *s)
			s++;
	}
	return (words);
}

void	*makefree(char **str)
{
	while (*str)
		free(*str);
	free(str);
	return (NULL);
}

char	**putword(char **str, const char *s, char delimiter)
{
	size_t	length;
	size_t	i;

	i = 0;
	while (*s)
	{
		length = 0;
		while (s[length] != delimiter && s[length])
			length++;
		str[i] = (char *) malloc(length * sizeof(char) + 1);
		if (str[i] == NULL)
			return (makefree(str));
		str[i][length] = '\0';
		while (length > 0)
		{
			str[i][length - 1] = s[length - 1];
			length--;
		}
		while (*s != delimiter && *s)
			s++;
		while (*s == delimiter && *s)
			s++;
		i++;
	}
	return (str);
}

char	**ft_split(char const *s, char delimiter)
{
	char	**str;
	size_t	words;

	words = wordsnum(s, delimiter);
	str = (char **) malloc((words + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	while (*s == delimiter && *s)
		s++;
	str = putword(str, s, delimiter);
	str[words] = NULL;
	return (str);
}
