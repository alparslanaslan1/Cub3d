/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:30:07 by bsen              #+#    #+#             */
/*   Updated: 2024/11/24 16:20:59 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "cub3d.h"

void	texture_control(t_data *data)
{
	int	i;

	i = 0;
	while (data->map2d[i])
	{
		chech_texture(data->map2d[i], data);
		i++;
		if (data->no_text && data->ea_text && data->we_text && data->so_text
			&& data->c && data->f)
			break ;
	}
	if (!data->no_text || !data->ea_text || !data->we_text || !data->so_text
		|| !data->c || !data->f)
		ft_exit("map texture error", data);
	data->where_am_i = i;
	char_control(data, i);
}

void	map_control(t_data *data)
{
	int	i;
	int	j;

	i = data->where_am_i;
	while (i < data->row_length)
	{
		j = 0;
		while (j < (int)ft_strlen(data->map2d[i]))
		{
			if (data->map2d[i][j] && (data->map2d[i][j] == 'N'
					|| data->map2d[i][j] == 'W' || data->map2d[i][j] == 'E'
					|| data->map2d[i][j] == 'S'))
			{
				data->player.y = i;
				data->player.x = j;
			}
			j++;
			if (data->longest_line < (int)ft_strlen(data->map2d[i]))
				data->longest_line = ft_strlen(data->map2d[i]);
		}
		i++;
	}
}

void	map_parsing(t_data *data)
{
	int		i;
	int		j;
	char	**virtual_map;
	int		x;

	virtual_map = NULL;
	x = 0;
	virtual_map = creat_vrmap(virtual_map, data);
	i = data->where_am_i - 1;
	while (data->map2d[++i])
	{
		j = -1;
		while (++j < data->longest_line)
		{
			if (data->map2d[i] && j < (int)ft_strlen(data->map2d[i])
				&& data->map2d[i][j])
				virtual_map[x][j] = data->map2d[i][j];
			else
				virtual_map[x][j] = '+';
		}
		x++;
	}
	find_player(virtual_map, data);
	map_playable(data, virtual_map, data->x, data->y);
	if (virtual_map != NULL)
		ft_free(virtual_map);
}

void	map_playable(t_data *data, char **i_map, int x, int y)
{
	if (map_null_check(i_map, x, y))
		ft_exit("Invalid map + unreachable area detected!", data);
	if ((i_map[y][x + 1] == '+') || (i_map[y][x - 1] == '+') || (i_map[y
			+ 1][x] == '+') || (i_map[y - 1][x] == '+'))
		ft_exit("Invalid map - unreachable area detected!", data);
	if (i_map[y][x + 1] == '0')
	{
		i_map[y][x + 1] = '2';
		map_playable(data, i_map, x + 1, y);
	}
	if (i_map[y][x - 1] == '0')
	{
		i_map[y][x - 1] = '2';
		map_playable(data, i_map, x - 1, y);
	}
	if (i_map[y + 1][x] == '0')
	{
		i_map[y + 1][x] = '2';
		map_playable(data, i_map, x, y + 1);
	}
	if (i_map[y - 1][x] == '0')
	{
		i_map[y - 1][x] = '2';
		map_playable(data, i_map, x, y - 1);
	}
}

int	controls(t_data *data)
{
	texture_control(data);
	texture_accesible(data);
	map1d(data);
	map_control(data);
	map_parsing(data);
	return (0);
}
