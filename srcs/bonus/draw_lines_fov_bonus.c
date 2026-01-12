/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines_fov.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:56:19 by anruiz-d          #+#    #+#             */
/*   Updated: 2025/12/12 18:59:54 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_bonus.h"

void	mm_put_pixel(t_data *data, t_minimap *map, t_posminimap p, int color)
{
	int		map_x;
	int		map_y;
	char	**grid;

	if (p.pos_x < 0 || p.pos_y < 0 || p.pos_x >= IMG_W || p.pos_y >= IMG_H)
		return ;
	grid = data->map;
	map_x = map->start_x + (p.pos_x - map->pos_minimap_x) / map->scale;
	map_y = map->start_y + (p.pos_y - map->pos_minimap_y) / map->scale;
	if (map_y < 0 || map_y >= minimap_height(grid))
		return ;
	if (map_x < 0 || map_x >= (int)ft_strlen(grid[map_y]))
		return ;
	if (grid[map_y][map_x] != '0')
		return ;
	put_pixel(&data->img, p.pos_x, p.pos_y, color);
}

void	draw_line(t_data *data, t_minimap *map, t_thick_line l)
{
	t_posminimap	p;
	t_vec			pos;
	t_vec			step;
	int				steps;

	pos.x = l.a.pos_x;
	pos.y = l.a.pos_y;
	steps = abs(l.b.pos_x - l.a.pos_x);
	if (steps < abs(l.b.pos_y - l.a.pos_y))
		steps = abs(l.b.pos_y - l.a.pos_y);
	if (steps == 0)
	{
		mm_put_pixel(data, map, l.a, l.color);
		return ;
	}
	step.x = (l.b.pos_x - l.a.pos_x) / (double)steps;
	step.y = (l.b.pos_y - l.a.pos_y) / (double)steps;
	while (steps-- >= 0)
	{
		p.pos_x = (int)pos.x;
		p.pos_y = (int)pos.y;
		mm_put_pixel(data, map, p, l.color);
		pos.x += step.x;
		pos.y += step.y;
	}
}
