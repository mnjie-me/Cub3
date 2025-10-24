/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:05:16 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/24 16:38:17 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

int	check_hit(t_data *data)
{
	if (data->ray.map_y < 0 || data->ray.map_y >= data->ray.map_h)
		return (1);
	if (data->ray.map_x < 0 || data->ray.map_x
		>= check_width(data->map, data->ray.map_y))
		return (1);
	if (data->map[data->ray.map_y][data->ray.map_x] == '1')
	{
		if (data->ray.side == 0)
			data->ray.perp_wall_dist = data->ray.side_dist_x
				- data->ray.delta_dist_x;
		else
			data->ray.perp_wall_dist = data->ray.side_dist_y
				- data->ray.delta_dist_y;
		return (1);
	}
	return (0);
}

void	dda(t_data *data)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		hit = check_hit(data);
	}
}

void	step_dist(t_data *data)
{
	if (data->ray.ray_dir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->pos.pos_x - data->ray.map_x)
			* data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - data->pos.pos_x)
			* data->ray.delta_dist_x;
	}
	if (data->ray.ray_dir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->pos.pos_y - data->ray.map_y)
			* data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - data->pos.pos_y)
			* data->ray.delta_dist_y;
	}
}

void	prep_ray(t_data *data, int x)
{
	data->ray.camera_x = 2.0 * x / (double)IMG_W - 1.0;
	data->ray.ray_dir_x = data->pos.dir_x + data->pos.plane_x
		* data->ray.camera_x;
	data->ray.ray_dir_y = data->pos.dir_y + data->pos.plane_y
		* data->ray.camera_x;
	if (data->ray.ray_dir_x == 0.0)
		data->ray.ray_dir_x = 1e-30;
	if (data->ray.ray_dir_y == 0.0)
		data->ray.ray_dir_y = 1e-30;
	data->ray.map_x = (int)data->pos.pos_x;
	data->ray.map_y = (int)data->pos.pos_y;
}

void	raycast(t_data *data)
{
	int	x;

	x = 0;
	init_ray(data);
	data->ray.map_w = check_width(data->map, data->ray.map_y);
	data->ray.map_h = check_height(data->map);
	while (x < IMG_W)
	{
		prep_ray(data, x);
		data->ray.delta_dist_x = fabs(1.0 / data->ray.ray_dir_x);
		data->ray.delta_dist_y = fabs(1.0 / data->ray.ray_dir_y);
		step_dist(data);
		dda(data);
		calculate_perp(data);
		draw_wall_column(data, x);
		ceil_floor_colors(data, x);
		x++;
	}
}
