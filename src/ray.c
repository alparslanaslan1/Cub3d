/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:33:57 by bsen              #+#    #+#             */
/*   Updated: 2024/11/24 14:20:20 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include "cub3d.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	compute_ray_properties(t_data *data, int x)
{
	// ray_screen_x = -1 ile +1 arasında bir değer alıyor. bunun nedni -1 nokası ekranın en solu +1 de en sağı ve biz bu noktanın arasında kalan her noktadan ışın göndereceğiz.
	data->ray_screen_x = 2 * x / (double)WIDTH - 1;
	// data.dir = bakış yönü.
	//data.raydir = ışın yönü. = bakış yönü + kamera düzlemi * kamera_x
	data->ray_direction[0] = data->dir[0] + data->camera_plane[0] * data->ray_screen_x;
	data->ray_direction[1] = data->dir[1] + data->camera_plane[1] * data->ray_screen_x;

	data->map_grid_pos[0] = (int)data->pos[0];
	data->map_grid_pos[1] = (int)data->pos[1];
	//delta.dist = ışıının çarptığı ızgaralar arasındaki mesafe.
	if (data->ray_direction[0] == 0)
		data->grid_step_dist[0] = 1e30;
	else
		data->grid_step_dist[0] = fabs(1 / data->ray_direction[0]);
	if (data->ray_direction[1] == 0)//----- bu iki if aynı işlemi konrtol ediyor. kod çalıştığı için bu if bloğunu silelim.
		data->ray_direction[1] = 0.001;//---------------------------------
	if (data->ray_direction[1] == 0)
		data->grid_step_dist[1] = 1e30;
	else
		data->grid_step_dist[1] = fabs(1 / data->ray_direction[1]);
}

void	compute_ray_step_and_distance(t_data *data)
{
	int	i;

	i = 0;
	// ışın bir hücrenin ortaasından başlıyor diyelim burda ışının hücre sınırına olan mesafesini hesaplıyoruz.
	// döngüde 2 kere kullanma amacı x ve y. raydir 0'dan küçükse -1 negatif yönde hareket ediyor demektir. 1 ise pozitif yönde hareket ediyor demektir.
	while (i < 2)
	{
		//data.step ışının hangi yönde hareket edeceğini belirler.
		if (data->ray_direction[i] < 0)
		{
			data->ray_step[i] = -1;
			// side.dist = ışının hücre sınırına olan mesafesi --- pos. hücrenin ortalarında olduyor. map pos tam sayıya yuvarlanmış hali. delta_dist ışının hücre sınırına olan mesafesi.
			data->border_dist[i] = (data->pos[i] - data->map_grid_pos[i])
				* data->grid_step_dist[i];
		}
		else
		{
			data->ray_step[i] = 1;
			data->border_dist[i] = (data->map_grid_pos[i] + 1.0 - data->pos[i])
				* data->grid_step_dist[i];
		}
		++i;
	}
}

void	calculate_collision_distance(t_data *data)
{
	int	next_grid_boundary;

	while (1)
	{
		if (data->border_dist[0] < data->border_dist[1]) // en yakın hücreeyi belirlemek için. 0 ise ilk olarak x eksenine ulaşır.
			next_grid_boundary = 0;
		else
			next_grid_boundary = 1;
		data->border_dist[next_grid_boundary] += data->grid_step_dist[next_grid_boundary];// ışın başlangıçtan duvara kadar olan mesafesini belirliyoruz. tek tek toplaYarak

		data->map_grid_pos[next_grid_boundary] += data->ray_step[next_grid_boundary];//ışın hangi hücrede belirle

		data->hit_axis = next_grid_boundary;  //ışın hangi ekseine çarptıysa onu belirle	.

		if ((data->map2d[data->map_grid_pos[1]][data->map_grid_pos[0]]) == '1')
			break ;
	}
}

void	compute_wall_dimensions_and_texture(t_data *data)
{

	data->perp_wall_dist = data->border_dist[data->hit_axis] // burda son hücreye gidip bir adım geri?
		- data->grid_step_dist[data->hit_axis];

	data->wall_height = (int)(HEIGHT / data->perp_wall_dist); //duvarın ekrandaki boyutu
	data->wall_top_pixel = -data->wall_height / 2 + HEIGHT / 2; // -data.line olmasının neden?

	if (data->wall_top_pixel < 0) //ekranın üstüne çıkarsa görüntü kayması oluyor bu yüzden 0 yapıyoruz.
		data->wall_top_pixel = 0;

	data->wall_bot_pixel = data->wall_height / 2 + HEIGHT / 2;

	if (data->wall_bot_pixel >= HEIGHT)//duvar ekranın alt sınırına aşınca görüntü bozuluyor.
		data->wall_bot_pixel = HEIGHT - 1;

	data->hit_point_x = data->pos[!data->hit_axis] + data->perp_wall_dist // burda data.pos[!data->side]'da !data side yerine 1 koyalım.  (ışının duvara çarğtığı notanın x kordinatı)
		* data->ray_direction[!data->hit_axis];

	data->hit_point_x -= (int)data->hit_point_x;

	data->tex_column[0] = (int)(data->hit_point_x * TEXWIDTH);

	if (data->hit_axis == 0 && data->ray_direction[0] < 0)//-----burayı anlamadım
		data->tex_column[0] = TEXWIDTH - data->tex_column[0] - 1;

	else if (data->hit_axis == 1 && data->ray_direction[1] > 0)
		data->tex_column[0] = TEXWIDTH - data->tex_column[0] - 1;//------  burayı anlamadım

	data->tex_step = (double)TEXHEIGHT / data->wall_height;

	data->tex_pos = (data->wall_top_pixel - HEIGHT / 2 + data->wall_height / 2)
		* data->tex_step;
}

void	render_column(t_data *data, int x, int y)
{
	while (++y < HEIGHT)
	{
		data->tex_column[1] = data->tex_pos;
		if (y < data->wall_top_pixel)// gökyüzünü çiziyoruz.
			set_pixel_color(data, x, y, data->colors[1]);
		else if (y > data->wall_bot_pixel)// zemini çiziyoruz.
			set_pixel_color(data, x, y, data->colors[0]);
		else		// duvarı çiziyoruz.
		{
			render_texture(data, x, y);
			data->tex_pos += data->tex_step;
		}
	}
}
