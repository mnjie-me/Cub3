/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:45:50 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/14 14:12:03 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	init_draw(t_data *data)
{
	data->draw.wall_height = 0;
	data->draw.start = 0;
	data->draw.end = 0;
}

int	check_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	check_width(char **map, int row)
{
	int	i;

	if (!map || !map[0])
		return (0);
	i = 0;
	while (map[row][i])
		i++;
	i -= 1;
	return (i);
}

void	init_ray(t_data *data)
{
	data->ray.map_h = 0;
	data->ray.map_w = 0;
	data->ray.map_x = 0;
	data->ray.map_y = 0;
	data->ray.step_x = 0;
	data->ray.step_y = 0;
	data->ray.side = 0;
	data->ray.camera_x = 0;
	data->ray.ray_dir_x = 0;
	data->ray.ray_dir_y = 0;
	data->ray.delta_dist_x = 0;
	data->ray.delta_dist_y = 0;
	data->ray.side_dist_x = 0;
	data->ray.side_dist_y = 0;
	data->ray.perp_wall_dist = 0;
}