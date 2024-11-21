/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:02:54 by alaslan           #+#    #+#             */
/*   Updated: 2023/12/22 10:14:10 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (s2[j] == '\0')
		return ((char *) &s1[i]);
	while (s1[i] && i < len)
	{
		if (s1[i + j] == s2[j] && (i + j) < len)
		{
			if (s2[j + 1] == '\0')
				return ((char *)&s1[i]);
			else
				j++;
		}
		else
		{
			i++;
			j = 0;
		}
	}
	return (NULL);
}
