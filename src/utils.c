/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:12:54 by alaslan           #+#    #+#             */
/*   Updated: 2024/11/24 16:21:33 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "cub3d.h"

int	map_null_check(char **map, int x, int y)
{
	if (x - 1 < 0 || y - 1 < 0)
		return (1);
	if (!map[y][x + 1] || !map[y][x - 1] || !map[y - 1][x] || !map[y + 1][x])
	{
		return (1);
	}
	else if (map[y][x] == '+' || map[y][x + 1] == '+' || map[y][x - 1] == '+'
		|| map[y - 1][x] == '+' || map[y + 1][x] == '+')
	{
		return (1);
	}
	else if (map[y][x] == ' ' || map[y][x + 1] == ' ' || map[y][x - 1] == ' '
		|| map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
		return (1);
	return (0);
}

void	map1d(t_data *data)
{
	int		start;
	char	*tmp;

	start = ft_strlen(data->map) - 1;
	while (data->map[start])
	{
		if (data->map[start] == 'C' || data->map[start] == 'F'
			|| (data->map[start] == 'N' && data->map[start + 1] == 'O')
			|| (data->map[start] == 'W' && data->map[start + 1] == 'E')
			|| (data->map[start] == 'S' && data->map[start + 1] == 'O')
			|| (data->map[start] == 'E' && data->map[start + 1] == 'A'))
			break ;
		start--;
	}
	while (data->map[start] != '\n')
		start++;
	tmp = ft_substr(data->map, start, ft_strlen(data->map));
	free(data->map);
	data->map = ft_strtrim(tmp, "\n");
	free(tmp);
	start = -1;
	while (data->map[++start])
		if (data->map[start] == '\n' && data->map[start + 1] == '\n')
			ft_exit("error\n newline error", data);
}

int	set_color(int *f_int, int *c_int, char **f, char **c)
{
	int	i;

	i = -1;
	while (f[++i] && i < 3)
		f_int[i] = ft_atoi(f[i]);
	if (i != 3)
		return (1);
	i = -1;
	while (c[++i] && i < 3)
		c_int[i] = ft_atoi(c[i]);
	if (i != 3)
		return (1);
	i = -1;
	while (++i < 3)
		if ((f_int[i] > 255 || f_int[i] < 0) || (c_int[i] > 255
				|| c_int[i] < 0))
			return (1);
	return (0);
}

char	**creat_vrmap(char **virtual_map, t_data *data)
{
	int	i;

	i = 0;
	virtual_map = (char **)malloc((sizeof(char *) * 256));
	if (!virtual_map)
		ft_exit("malloc error", data);
	printf("data.long%d\n", data->longest_line);
	printf("data.row%d\n", data->row_length);
	while (i < data->row_length)
	{
		virtual_map[i] = (char *)malloc((sizeof(char) * 1024)
				+ 1);
		if (!virtual_map[i])
			ft_free(virtual_map);
		ft_bzero(virtual_map[i], data->longest_line + 1);
		i++;
	}
	return (virtual_map);
}

void	chech_texture(char *s, t_data *data)
{
	if (ft_strncmp(s, "NO ", 3) == 0)
		data->no_text = ft_substr(s, 3, ft_strlen(s));
	else if (ft_strncmp(s, "WE ", 3) == 0)
		data->we_text = ft_substr(s, 3, ft_strlen(s));
	else if (ft_strncmp(s, "SO ", 3) == 0)
		data->so_text = ft_substr(s, 3, ft_strlen(s));
	else if (ft_strncmp(s, "EA ", 3) == 0)
		data->ea_text = ft_substr(s, 3, ft_strlen(s));
	else if (ft_strncmp(s, "F ", 2) == 0)
		data->f = ft_substr(s, 2, ft_strlen(s));
	else if (ft_strncmp(s, "C ", 2) == 0)
		data->c = ft_substr(s, 2, ft_strlen(s));
	// 	if (data->no_text == NULL || data->we_text == NULL
	// 		|| data->so_text == NULL || data->ea_text == NULL || data->f == NULL
	// 		|| data->c == NULL)
	// 		ft_exit("hata", data);
}
