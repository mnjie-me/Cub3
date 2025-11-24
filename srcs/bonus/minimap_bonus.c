/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruiz-d <anruiz-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 02:22:47 by anruiz-d          #+#    #+#             */
/*   Updated: 2025/11/24 17:00:49 by anruiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_bonus.h"

void	init_data_mm(t_data *data, t_minimap *map)
{
	map->map_width = minimap_width(data->map);
	map->map_height = minimap_height(data->map);
	map->radius = 2;
	map->size_mmap = 140;
	map->view_width = map->radius * 2 + 1;
	if (map->view_width > map->map_width)
		map->view_width = map->map_width;
	map->view_height = map->radius * 2 + 1;
	if (map->view_height > map->map_height)
		map->view_height = map->map_height;
	map->scale = map->size_mmap / map->view_width;
	map->height = map->scale * map->view_height;
	map->width = map->scale * map->view_width;
	map->pos_minimap_x = IMG_W - map->width - 20;
	map->pos_minimap_y = 20;
	map->start_x = (int)data->pos.pos_x - map->radius;
	map->start_y = (int)data->pos.pos_y - map->radius;
}

void	conf_view_map(t_minimap *map)
{
	int	player_x;
	int	player_y;

	player_x = map->start_x;
	player_y = map->start_y;
	if (player_x < 0)
		player_x = 0;
	if (player_y < 0)
		player_y = 0;
	if (map->view_width > map->map_width)
		player_x = 0;
	else if (player_x + map->view_width > map->map_width)
		player_x = map->map_width - map->view_width;
	if (map->view_height > map->map_height)
		player_y = 0;
	else if (player_y + map->view_height > map->map_height)
		player_y = map->map_height - map->view_height;
	map->start_x = player_x;
	map->start_y = player_y;
}

void	minimap_rect(t_img *img, t_minimap *map, t_layer layer)
{
	t_rect	rect;

	if (layer == BACKGROUND)
	{
		rect.start_x = map->pos_minimap_x - 6;
		rect.start_y = map->pos_minimap_y - 6;
		rect.width = map->width + 12;
		rect.height = map->height + 12;
		rect.color = 0x454545;
	}
	else if (layer == BORDER)
	{
		rect.start_x = map->pos_minimap_x - 4;
		rect.start_y = map->pos_minimap_y - 4;
		rect.width = map->width + 8;
		rect.height = map->height + 8;
		rect.color = 0x2A2A2A;
	}
	rect.y = -1;
	while (++rect.y < rect.height)
	{
		rect.x = -1;
		while (++rect.x < rect.width)
			put_pixel(img, rect.start_x + rect.x, rect.start_y + rect.y, rect.color);
	}
}

void	draw_minimap(t_data *data)
{
	t_minimap	map;

	init_data_mm(data, &map);
	conf_view_map(&map);
	minimap_rect(&data->img, &map, BACKGROUND);
	minimap_rect(&data->img, &map, BORDER);
	draw_short_map(data, &map);
	map.pos_player.pos_x
		= map.pos_minimap_x + (data->pos.pos_x - map.start_x) * map.scale;
	map.pos_player.pos_y
		= map.pos_minimap_y + (data->pos.pos_y - map.start_y) * map.scale;
	fill_fov(data, &map);
	draw_player(data, &map);
}
