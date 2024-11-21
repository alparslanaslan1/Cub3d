/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:08:27 by alaslan           #+#    #+#             */
/*   Updated: 2023/12/22 09:20:53 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t t)
{
	size_t	s;
	size_t	d;
	size_t	i;

	i = 0;
	d = ft_strlen(dst);
	s = ft_strlen((char *)src);
	if (t < d)
		return (t + s);
	while (src[i] && (d + i + 1) < t)
	{
		dst[d + i] = src[i];
		i++;
	}
	dst[d + i] = '\0';
	return ((d + s));
}
