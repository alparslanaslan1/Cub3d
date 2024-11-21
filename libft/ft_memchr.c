/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:36:56 by alaslan           #+#    #+#             */
/*   Updated: 2024/07/28 13:36:57 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		ch;
	unsigned const char	*str;

	ch = c;
	str = (unsigned const char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == ch)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
