/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpaslan <alpaslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:14:20 by bsen              #+#    #+#             */
/*   Updated: 2024/11/22 23:24:40 by alpaslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../minilibx/mlx.h"

void	set_pixel_color(t_data *data, int x, int y, int color)
{
	//data->image->addr = ekran belleğimie erişim için
	//y * WIDTH + x = x ve y koordinatlarındaki pikselin adresi
	data->image->addr[y * WIDTH + x] = color;
}

void	render_texture(t_data *data, int x, int y)
{
	if (data->side == 1) // kzuey veya güney
	{
		if (data->raydir[1] < 0)//raydir[1] negatifses ışın kuzueye çarpıyor demektir. ve north image basıyız bu yüzden.
			set_pixel_color(data, x, y, data->north->addr[TEXHEIGHT
				* data->tex[1] + data->tex[0]]);
		else
			set_pixel_color(data, x, y, data->south->addr[TEXHEIGHT
				* data->tex[1] + data->tex[0]]);
	}
	else
	{
		if (data->raydir[0] < 0)
			set_pixel_color(data, x, y, data->west->addr[TEXHEIGHT
				* data->tex[1] + data->tex[0]]);
		else
			set_pixel_color(data, x, y, data->east->addr[TEXHEIGHT
				* data->tex[1] + data->tex[0]]);
	}
}

void	ft_mlx2(t_data *data, int c)
{
	data->north->image = mlx_xpm_file_to_image(data->mlx_ptr, "north.xpm", &c,
			&c);
	data->south->image = mlx_xpm_file_to_image(data->mlx_ptr, "south.xpm", &c,
			&c);
	data->west->image = mlx_xpm_file_to_image(data->mlx_ptr, "west.xpm", &c,
			&c);
	data->east->image = mlx_xpm_file_to_image(data->mlx_ptr, "east.xpm", &c,
			&c);
	if (!data->north->image || !data->south->image || !data->west->image
		|| !data->east->image)
		ft_exit("hata", data);
	data->north->addr = (int *)mlx_get_data_addr(data->north->image, &c, &c,
			&c);
	data->south->addr = (int *)mlx_get_data_addr(data->south->image, &c, &c,
			&c);
	data->west->addr = (int *)mlx_get_data_addr(data->west->image, &c, &c, &c);
	data->east->addr = (int *)mlx_get_data_addr(data->east->image, &c, &c, &c);
	if (!data->north->addr || !data->south->addr || !data->west->addr
		|| !data->east->addr)
		ft_exit("hata", data);
}

void	xpm_init(t_data *data, int a, int b)
{
	data->image = malloc(sizeof(t_image));
	data->north = malloc(sizeof(t_image));
	data->south = malloc(sizeof(t_image));
	data->west = malloc(sizeof(t_image));
	data->east = malloc(sizeof(t_image));
	if (!data->image || !data->north || !data->south || !data->west
		|| !data->east)
		ft_exit("hata", data);
	data->image->image = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->image->image)
		ft_exit("hata", data);
	data->image->addr = (int *)mlx_get_data_addr(data->image->image, &a, &a,
			&a);
	if (!data->image->addr)
		ft_exit("hata", data);
	ft_mlx2(data, b);
}

void	mlx_create(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		ft_exit("mlx error", data);
	data->win = mlx_new_window(data->mlx_ptr, 720, 550, "cub3d");
	if (!data->win)
		ft_exit("mlx error", data);
}
