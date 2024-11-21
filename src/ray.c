/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpaslan <alpaslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:33:57 by bsen              #+#    #+#             */
/*   Updated: 2024/11/21 02:53:55 by alpaslan         ###   ########.fr       */
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

void	calculate_ray_direction_and_distances(t_data *data, int x)
{
	// camera_x = -1 ile +1 arasında bir değer alıyor. bunun nedni -1 nokası ekranın en solu +1 de en sağı ve biz bu noktanın arasında kalan her noktadan ışın göndereceğiz.
	data->camera_x = 2 * x / (double)WIDTH - 1;
	// data.dir = bakış yönü.
	//data.raydir = ışın yönü. = bakış yönü + kamera düzlemi * kamera_x
	data->raydir[0] = data->dir[0] + data->plane[0] * data->camera_x;
	data->raydir[1] = data->dir[1] + data->plane[1] * data->camera_x;
	data->map_pos[0] = (int)data->pos[0];
	data->map_pos[1] = (int)data->pos[1];
	//delta.dist = ışıının çarptığı ızgaralar arasındaki mesafe.
	if (data->raydir[0] == 0)
		data->delta_dist[0] = 1e30;
	else
		data->delta_dist[0] = fabs(1 / data->raydir[0]);
	if (data->raydir[1] == 0)//----- bu iki if aynı işlemi konrtol ediyor. kod çalıştığı için bu if bloğunu silelim.
		data->raydir[1] = 0.001;//---------------------------------
	if (data->raydir[1] == 0)
		data->delta_dist[1] = 1e30;
	else
		data->delta_dist[1] = fabs(1 / data->raydir[1]);
}

void	calculate_step(t_data *data)
{
	int	i;

	i = 0;
	// ışın bir hücrenin ortaasından başlıyor diyelim burda ışının hücre sınırına olan mesafesini hesaplıyoruz.
	// döngüde 2 kere kullanma amacı x ve y. raydir 0'dan küçükse -1 negatif yönde hareket ediyor demektir. 1 ise pozitif yönde hareket ediyor demektir.
	while (i < 2)
	{
		//data.step ışının hangi yönde hareket edeceğini belirler.
		// printf("data.pos[%d] = %f\n", i, data->pos[i]);
		// printf("data.map_pos[%d] = %d\n", i, data->map_pos[i]);
		// printf("data.delta_dist[%d] = %f\n", i, data->delta_dist[i]);
		if (data->raydir[i] < 0)
		{
			data->step[i] = -1;
			// side.dist = ışının hücre sınırına olan mesafesi --- pos. hücrenin ortalarında olduyor. map pos tam sayıya yuvarlanmış hali. delta_dist ışının hücre sınırına olan mesafesi.
			data->side_dist[i] = (data->pos[i] - data->map_pos[i])
				* data->delta_dist[i];
		}
		else
		{
			data->step[i] = 0;
			data->side_dist[i] = (data->map_pos[i] + 1.0 - data->pos[i])
				* data->delta_dist[i];
		}
		++i;
	}
}

void	calculate_collision_distance(t_data *data)
{
	int	nearest_wall;

	while (1)
	{
		if (data->side_dist[0] < data->side_dist[1]) // en yakın hücreeyi belirlemek için. 0 ise ilk olarak x eksenine ulaşır.
			nearest_wall = 0;
		else
			nearest_wall = 1;
		data->side_dist[nearest_wall] += data->delta_dist[nearest_wall];// ışın başlangıçtan duvara kadar olan mesafesini belirliyoruz. tek tek toplaYarak

		data->map_pos[nearest_wall] += data->step[nearest_wall];//ışın hangi hücrede belirle

		data->side = nearest_wall;  //ışın hangi ekseine çarptıysa onu belirle	.

		if ((data->map2d[data->map_pos[1]][data->map_pos[0]]) == '1')
			break ;
	}
}

void	calculate_wall_properties(t_data *data)
{

	data->perp_wall_dist = data->side_dist[data->side] // burda son hücreye gidip bir adım geri?
		- data->delta_dist[data->side];

	data->line_h = (int)(HEIGHT / data->perp_wall_dist); //duvarın ekrandaki boyutu
	data->draw_start = -data->line_h / 2 + HEIGHT / 2; // -data.line olmasının neden?

	if (data->draw_start < 0) //ekranın üstüne çıkarsa görüntü kayması oluyor bu yüzden 0 yapıyoruz.
		data->draw_start = 0;

	data->draw_end = data->line_h / 2 + HEIGHT / 2;

	if (data->draw_end >= HEIGHT)//duvar ekranın alt sınırına aşınca görüntü bozuluyor.
		data->draw_end = HEIGHT - 1;

	data->wall_x = data->pos[!data->side] + data->perp_wall_dist
		* data->raydir[!data->side];

	data->wall_x -= (int)data->wall_x;

	data->tex[0] = (int)(data->wall_x * TEXWIDTH);

	if (data->side == 0 && data->raydir[0] < 0)
		data->tex[0] = TEXWIDTH - data->tex[0] - 1;

	else if (data->side == 1 && data->raydir[1] > 0)
		data->tex[0] = TEXWIDTH - data->tex[0] - 1;

	data->step_size = (double)TEXHEIGHT / data->line_h;

	data->tex_pos = (data->draw_start - HEIGHT / 2 + data->line_h / 2)
		* data->step_size;
}

void	render_column(t_data *data, int x, int y)
{
	while (++y < HEIGHT)
	{
		data->tex[1] = data->tex_pos;
		if (y < data->draw_start)
			set_pixel_color(data, x, y, data->colors[1]);
		else if (y > data->draw_end)
			set_pixel_color(data, x, y, data->colors[0]);
		else
		{
			render_texture(data, x, y);
			data->tex_pos += data->step_size;
		}
	}
}
