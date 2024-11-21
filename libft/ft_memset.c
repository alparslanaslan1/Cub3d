/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:19:23 by alaslan           #+#    #+#             */
/*   Updated: 2023/12/21 15:44:18 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t l)
{
	char	*pstr;
	size_t	i;

	pstr = (char *)str;
	i = 0;
	while (i < l)
	{
		pstr[i] = (char)c;
		i++;
	}
	return (pstr);
}
