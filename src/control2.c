/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsen <bsen@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:34:25 by bsen              #+#    #+#             */
/*   Updated: 2024/11/19 19:18:29 by bsen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "cub3d.h"

void	select_player(char a, t_data *data)
{
	if (a == 'N')
	{
		data->char_count++;
		data->player.player_dir = 'N';
	}
	else if (a == 'E')
	{
		data->char_count++;
		data->player.player_dir = 'E';
	}
	else if (a == 'S')
	{
		data->char_count++;
		data->player.player_dir = 'S';
	}
	else if (a == 'W')
	{
		data->char_count++;
		data->player.player_dir = 'W';
	}
	else if (a != '1' && a != '0' && a != ' ' && a != '\n')
		ft_exit("map charackter error", data);
}

void	char_control(t_data *data, int y)
{
	int	x;

	x = 0;
	while (data->map2d[y])
	{
		x = 0;
		while (data->map2d[y][x])
		{
			select_player(data->map2d[y][x], data);
			x++;
		}
		y++;
	}
	if (data->char_count != 1)
		ft_exit("charackter error", data);
	data->row_length = y;
}

void	texture_accesible(t_data *data)
{
	int	fd;

	fd = open(data->so_text, O_RDONLY);
	if ((fd) == -1)
		ft_exit("texture could not be opened", data);
	close(fd);
	fd = open(data->we_text, O_RDONLY);
	if ((fd) == -1)
		ft_exit("texture could not be opened", data);
	close(fd);
	fd = open(data->ea_text, O_RDONLY);
	if ((fd) == -1)
		ft_exit("texture could not be opened", data);
	close(fd);
	fd = open(data->no_text, O_RDONLY);
	if ((fd) == -1)
		ft_exit("texture could not be opened", data);
	close(fd);
	colorcode(data->f, data->c, data, 0);
}

void	colorcode(char *f_code, char *c_code, t_data *data, int j)
{
	char	**f;
	char	**c;
	int		f_int[3];
	int		c_int[3];
	int		i;

	i = -1;
	j = 0;
	clear_color(&f,&c,f_code,c_code);
	while (f[++i] && c[i] && i < 3)
	{
		j = -1;
		while (f[i][++j] && c[i][j])
			if (!ft_isdigit(f[i][j]) || !ft_isdigit(c[i][j]))
				ft_exit("number requeired", data);
	}
	if (set_color(f_int, c_int, f, c))
		ft_exit("colour not enough", data);
	data->colors[0] = (f_int[0] << 16) + (f_int[1] << 8) + f_int[2];
	data->colors[1] = (c_int[0] << 16) + (c_int[1] << 8) + c_int[2];
	ft_free(f);
	ft_free(c);
}

void	find_player(char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (j < data->longest_line)
		{
			if (map[i][j] && (map[i][j] == 'N' || map[i][j] == 'W'
					|| map[i][j] == 'E' || map[i][j] == 'S'))
			{
				data->y = i;
				data->x = j;
				return ;
			}
			j++;
		}
		i++;
	}
}
