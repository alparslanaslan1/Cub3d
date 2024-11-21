/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_made_of_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 07:18:12 by alaslan           #+#    #+#             */
/*   Updated: 2024/08/15 07:18:14 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_made_of_char(const char *str, char ch)
{
	if (str == NULL || *str == '\0')
	{
		return (1);
	}
	while (*str != '\0')
	{
		if (*str != ch)
		{
			return (0);
		}
		str++;
	}
	return (1);
}
