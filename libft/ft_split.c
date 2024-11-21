/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:10:01 by alaslan           #+#    #+#             */
/*   Updated: 2024/10/17 08:43:57 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_scount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	count = 1;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static int	ft_ccount(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_no_malloc(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		x;
	int		y;

	str = (char **)malloc(sizeof(char *) * (ft_scount(s, c) + 1));
	if (!str)
		return (NULL);
	x = -1;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			str[++x] = (char *)malloc(sizeof(char) * (ft_ccount(s, c) + 1));
			if (!str[x])
				return (ft_no_malloc(str));
			y = 0;
			while (*s && *s != c)
				str[x][y++] = *s++;
			str[x][y] = '\0';
		}
	}
	str[++x] = NULL;
	return (str);
}
