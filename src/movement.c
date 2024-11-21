/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsen <bsen@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:34:03 by bsen              #+#    #+#             */
/*   Updated: 2024/11/15 21:47:47 by bsen             ###   ########.fr       */
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
	double	oldirx;
	double	oldplanex;
	double	rotationangle;

	if (data->right)
		rotationangle = data->player.rot;
	else if (data->left)
		rotationangle = -data->player.rot;
	if (data->right || data->left)
	{
		oldirx = data->dir[0];
		data->dir[0] = data->dir[0] * cos(rotationangle) - data->dir[1]
			* sin(rotationangle);
		data->dir[1] = oldirx * sin(rotationangle) + data->dir[1]
			* cos(rotationangle);
		oldplanex = data->plane[0];
		data->plane[0] = data->plane[0] * cos(rotationangle) - data->plane[1]
			* sin(rotationangle);
		data->plane[1] = oldplanex * sin(rotationangle) + data->plane[1]
			* cos(rotationangle);
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
		move_x = -data->plane[0] * data->player.speed;
		move_y = -data->plane[1] * data->player.speed;
		move_player(data, move_x, move_y);
	}
	if (data->d)
	{
		move_x = data->plane[0] * data->player.speed;
		move_y = data->plane[1] * data->player.speed;
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
