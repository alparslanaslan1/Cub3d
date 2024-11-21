/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_play.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpaslan <alpaslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:47:04 by alaslan           #+#    #+#             */
/*   Updated: 2024/11/21 02:26:25 by alpaslan         ###   ########.fr       */
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

int	key_press(int keyCode, t_data *data)
{
	if (keyCode == 53)
		exit(0);//------------
	if (keyCode == 13)
		data->w = true;
	if (keyCode == 1)
		data->s = true;
	if (keyCode == 0)
		data->a = true;
	if (keyCode == 2)
		data->d = true;
	if (keyCode == RIGHT_ARROW)
		data->right = true;
	if (keyCode == LEFT_ARROW)
		data->left = true;
	return (0);
}

int	key_unpress(int keyCode, t_data *data)
{
	if (keyCode == 13)
		data->w = false;
	if (keyCode == 1)
		data->s = false;
	if (keyCode == 0)
		data->a = false;
	if (keyCode == 2)
		data->d = false;
	if (keyCode == RIGHT_ARROW)
		data->right = false;
	if (keyCode == LEFT_ARROW)
		data->left = false;
	return (0);
}

static void	raycast(t_data *data)
{
	int	x;

	x = -1;
	while (++x < 720) // Ekranın genişliği boyunca döngü
	{
		calculate_ray_direction_and_distances(data, x);
			// Işın yönü ve mesafelerini hesaplar
		calculate_step(data);
			// Işın adımını ve çarpma noktasını hesaplar
		calculate_collision_distance(data);
			// Işın çarptığı duvara kadar olan mesafeyi hesaplar
		calculate_wall_properties(data);
			// Duvar özelliklerini hesaplar
		render_column(data, x, -1);
			// Duvarı sütun olarak çizer
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win, data->image->image, 0, 0);
		// Çizilen görüntüyü pencereye aktarır
}

// Oyun döngüsü için ana fonksiyon
int	gamefunc(t_data *data)
{
	handle_movement(data, 0, 0); // Oyuncu hareketlerini işler
	rotate(data);                // Oyuncu dönüşünü işler
	raycast(data);               // Raycasting fonksiyonunu çağırır
	return (0);
}

void clear_color(char ***f, char ***c, char *f_code, char *c_code)
{
	char *tmp1;
	char *tmp2;

	tmp1 = ft_strtrim(f_code, " ");
	tmp2 = ft_strtrim(c_code, " ");
	*f = ft_split(tmp1, ',');
	*c = ft_split(tmp2, ',');
	free(tmp1);
	free(tmp2);
}
