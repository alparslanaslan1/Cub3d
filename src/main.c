/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsen <bsen@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:15:40 by bsen              #+#    #+#             */
/*   Updated: 2024/11/16 03:48:17 by bsen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include "cub3d.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	file_control(t_data *data)
{
	int	len;
	int	fd;

	len = ft_strlen(data->mapname);
	if (data->mapname[len - 4] != '.' || data->mapname[len - 3] != 'c'
		|| data->mapname[len - 2] != 'u' || data->mapname[len - 1] != 'b')
		ft_exit("file extension is incorrect", data);
	fd = open(data->mapname, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		ft_exit("file could not be opened", data);
	}
	close(fd);
}

char	*private_line(char *tmp, char *line, int fd)
{
	return (free(tmp), free(line), get_next_line(fd));
}

int	read_map(t_data *data)
{
	char	*line;
	char	*tmp;

	data->fd = open(data->mapname, O_RDONLY);
	line = get_next_line(data->fd);
	if (!line)
		ft_exit("hata", data);
	data->row_length++;
	data->map = ft_strdup(line);
	if (!data->map)
		ft_exit("hata", data);
	tmp = ft_strdup(line);
	if (!tmp)
		ft_exit("hata", data);
	while (line)
	{
		line = private_line(tmp, line, data->fd);
		if (!line)
			break ;
		data->row_length++;
		tmp = ft_strdup(data->map);
		free(data->map);
		data->map = ft_strjoin(tmp, line);
	}
	return (data->map2d = ft_split(data->map, '\n'), close(data->fd), 0);
}

void	data_init(t_data *data)
{
	data->c = NULL;
	data->f = NULL;
	data->ea_text = NULL;
	data->no_text = NULL;
	data->so_text = NULL;
	data->we_text = NULL;
	data->map2d = NULL;
	data->map = NULL;
	data->char_count = 0;
	data->row_length = 0;
	data->longest_line = 0;
	data->player.player_dir = 0;
	data->a = 0;
	data->w = 0;
	data->d = 0;
	data->s = 0;
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		data.mapname = av[1];
		file_control(&data);
		data_init(&data);
		read_map(&data);
		controls(&data);
		game_create(&data);
		mlx_hook(data.win, 2, 0, key_press, &data);
		mlx_hook(data.win, 3, 0, key_unpress, &data);
		mlx_hook(data.win, 17, 0, ft_exit, "finish");
		mlx_loop_hook(data.mlx_ptr, &gamefunc, &data);
		mlx_loop(data.mlx_ptr);
	}
	ft_exit("", &data);
}
