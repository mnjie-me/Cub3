/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:05:57 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/14 12:15:03 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	init_draw(t_data *data)
{
	data->draw.wall_height = 0;
	data->draw.start = 0;
	data->draw.end = 0;
}

void	calculate_perp(t_data *data)
{
	double	wall_height;
	int		start;
	int		end;

	wall_height = (int)(IMG_H / data->ray.perp_wall_dist);
	start = -wall_height / 2 + IMG_H / 2;
	end = wall_height / 2 + IMG_H / 2;
	if (start < 0)
		start = 0;
	if (end >= IMG_H)
		end = IMG_H - 1;
	data->draw.wall_height = wall_height;
	data->draw.start = start;
	data->draw.end = end;
	if (data->ray.side == 0)
		data->ray.wall_x = data->pos.pos_y + data->ray.perp_wall_dist * data->ray.ray_dir_y;
	else
		data->ray.wall_x = data->pos.pos_x + data->ray.perp_wall_dist * data->ray.ray_dir_x;
	data->ray.wall_x -= floor(data->ray.wall_x);
}


