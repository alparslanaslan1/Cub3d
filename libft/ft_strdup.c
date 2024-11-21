/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpaslan <alpaslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:29:56 by alaslan           #+#    #+#             */
/*   Updated: 2024/08/16 00:12:38 by alpaslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*s2;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	s2 = (char *)malloc((len + 1));
	if (!s2)
		return (NULL);
	ft_memmove (s2, str, len + 1);
	return (s2);
}
