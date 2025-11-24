/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruiz-d <anruiz-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:18:30 by anruiz-d          #+#    #+#             */
/*   Updated: 2025/11/24 17:01:10 by anruiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_bonus.h"

static	void	draw_tile(t_data *data, t_minimap *map, t_tile tile)
{
	t_rect	rect;

	rect.start_x = map->pos_minimap_x + tile.x * map->scale;
	rect.start_y = map->pos_minimap_y + tile.y * map->scale;
	rect.width = map->scale;
	rect.height = map->scale;
	rect.color = cell_color(tile.cell);
	rect.y = -1;
	while (++rect.y < rect.height)
	{
		rect.x = -1;
		while (++rect.x < rect.width)
			put_pixel(&data->img,
				rect.start_x + rect.x,
				rect.start_y + rect.y,
				rect.color);
	}
}

static	void	draw_map_row(t_data *data, t_minimap *map, int view_y, char *row)
{
	int		row_len;
	int		x;
	int		map_x;
	t_tile	tile;

	row_len = (int)ft_strlen(row);
	x = 0;
	while (x < map->view_width)
	{
		map_x = map->start_x + x;
		if (map_x >= 0 && map_x < row_len)
		{
			tile.x = x;
			tile.y = view_y;
			tile.cell = row[map_x];
			if (tile.cell != ' ')
				draw_tile(data, map, tile);
		}
		x++;
	}
}

void draw_short_map(t_data *data, t_minimap *map)
{
	int		y;
	int		map_y;
	char	*row;

	y = 0;
	while (y < map->view_height)
	{
		map_y = map->start_y + y;
		if (map_y >= 0 && map_y < map->map_height && data->map[map_y])
		{
			row = data->map[map_y];
			draw_map_row(data, map, y, row);
		}
		y++;
	}
}
