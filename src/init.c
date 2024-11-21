/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsen <bsen@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:46:58 by alaslan           #+#    #+#             */
/*   Updated: 2024/11/19 17:19:12 by bsen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include "cub3d.h"
#include <stdbool.h>
#include <stdio.h>

void	init2(t_data *data)
{
	data->map_pos[1] = 0;
	data->delta_dist[0] = 0;
	data->delta_dist[1] = 0;
	data->step[0] = 0;
	data->step[1] = 0;
	data->side_dist[0] = 0;
	data->side_dist[1] = 0;
	data->side = 0;
	data->perp_wall_dist = 0;
	data->line_h = 0;
	data->draw_start = 0;
	data->draw_end = 0;
	data->wall_x = 0;
	data->tex[0] = 0;
	data->tex[1] = 0;
	data->step_size = 0;
	data->tex_pos = 0;
}

void	player_init(t_data *data)
{
	data->player.x += 0.5;
	data->player.y += 0.5;
	data->player.dir = 0;
	data->player.speed = 0.06;
	data->player.rot = 0.03;
	data->left = false;
	data->right = false;
	data->dir[0] = 0;
	data->dir[1] = 0;
	data->plane[0] = 0;
	data->plane[1] = 0;
	data->pos[0] = data->player.x;
	data->pos[1] = data->player.y;
	data->raydir[0] = 0;
	data->raydir[1] = 0;
	data->camera_x = 0;
	data->map_pos[0] = 0;
	init2(data);
}

static bool	east_west(t_data *data)
{
	if (data->player.player_dir == 'W')
	{
		data->dir[0] = -1;
		data->dir[1] = 0;
		data->plane[0] = 0;
		data->plane[1] = -0.66;
		return (true);
	}
	else if (data->player.player_dir == 'E')
	{
		data->dir[0] = 1;
		data->dir[1] = 0;
		data->plane[0] = 0;
		data->plane[1] = 0.66;
		return (true);
	}
	return (false);
}

static bool	south_north(t_data *data)
{
	if (data->player.player_dir == 'S')
	{
		data->dir[0] = 0;
		data->dir[1] = 1;
		data->plane[0] = -0.66;
		data->plane[1] = 0;
		return (true);
	}
	else if (data->player.player_dir == 'N')
	{
		data->dir[0] = 0;
		data->dir[1] = -1;
		data->plane[0] = 0.66;
		data->plane[1] = 0;
		return (true);
	}
	return (false);
}

bool	check_player(t_data *data)
{
	if (east_west(data))
		return (true);
	if (south_north(data))
		return (true);
	return (false);
}
