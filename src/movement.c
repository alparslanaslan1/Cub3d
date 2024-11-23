/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpaslan <alpaslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:34:03 by bsen              #+#    #+#             */
/*   Updated: 2024/11/23 18:42:52 by alpaslan         ###   ########.fr       */
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

void	rotate(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotation_angle;

	if (data->right)
		rotation_angle = data->player.rot;
	else if (data->left)
		rotation_angle = -data->player.rot;
	if (data->right || data->left)
	{
		old_dir_x = data->dir[0];
		data->dir[0] = data->dir[0] * cos(rotation_angle) - data->dir[1]
			* sin(rotation_angle);
		data->dir[1] = old_dir_x * sin(rotation_angle) + data->dir[1]
			* cos(rotation_angle);
		old_plane_x = data->camera_plane[0];
		data->camera_plane[0] = data->camera_plane[0] * cos(rotation_angle) - data->camera_plane[1]
			* sin(rotation_angle);
		data->camera_plane[1] = old_plane_x * sin(rotation_angle) + data->camera_plane[1]
			* cos(rotation_angle);
	}
}

void	move_player(t_data *data, double _movex, double _movey)
{
	if (data->map2d[(int)(data->pos[1])][(int)(data->pos[0] + _movex)] != '1')
		data->pos[0] += _movex;
	if (data->map2d[(int)(data->pos[1] + _movey)][(int)(data->pos[0])] != '1')
		data->pos[1] += _movey;
}

void	handle_movement(t_data *data, double move_x, double move_y)
{
	if (data->a)
	{
		move_x = -data->camera_plane[0] * data->player.speed;
		move_y = -data->camera_plane[1] * data->player.speed;
		move_player(data, move_x, move_y);
	}
	if (data->d)
	{
		move_x = data->camera_plane[0] * data->player.speed;
		move_y = data->camera_plane[1] * data->player.speed;
		move_player(data, move_x, move_y);
	}
	if (data->w)
	{
		move_x = data->dir[0] * data->player.speed;
		move_y = data->dir[1] * data->player.speed;
		move_player(data, move_x, move_y);
	}
	if (data->s)
	{
		move_x = -data->dir[0] * data->player.speed;
		move_y = -data->dir[1] * data->player.speed;
		move_player(data, move_x, move_y);
	}
}
