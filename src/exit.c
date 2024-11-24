/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 04:12:03 by alaslan           #+#    #+#             */
/*   Updated: 2024/11/24 15:58:57 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "cub3d.h"

void	ft_free(char **s)
{
	int	i;

	i = -1;
	if (!s)
		return;
	while (s[++i] != NULL)
	{
		free(s[i]);
		s[i] = NULL;
	}
	free(s);
	s = NULL;

}

void	free_texture(t_data *data)
{
	if (data->so_text)
		free(data->so_text);
	if (data->we_text)
		free(data->we_text);
	if (data->no_text)
		free(data->no_text);
	if (data->ea_text)
		free(data->ea_text);
	if (data->f)
		free(data->f);
	if (data->c)
		free(data->c);
}

int	ft_exit(char *error_massage, t_data *data)
{
	if (data->map)
		free(data->map);
	if (data->map2d)
		ft_free(data->map2d);
	free_texture(data);
	printf("%s", error_massage);
	exit(1);
}

int	exit_cross()
{
	exit(1);
}
