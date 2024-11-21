/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsen <bsen@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 21:08:58 by bsen              #+#    #+#             */
/*   Updated: 2024/10/16 20:02:30 by bsen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*free_buffer(char **buffer, int i)
{
	char	*line;

	if (!*buffer)
		return (NULL);
	if (i == 0)
	{
		if (*buffer)
		{
			free(*buffer);
			*buffer = 0;
		}
		return (NULL);
	}
	else if (i == 1)
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = 0;
		return (line);
	}
	return (NULL);
}
