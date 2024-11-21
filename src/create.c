/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsen <bsen@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:18:47 by bsen              #+#    #+#             */
/*   Updated: 2024/11/19 17:19:06 by bsen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_create(t_data *data)
{
	player_init(data);
	check_player(data);
	mlx_create(data);
	xpm_init(data, 0, 0);
}
