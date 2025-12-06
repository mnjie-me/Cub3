/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruiz-d <anruiz-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:26:58 by anruiz-d          #+#    #+#             */
/*   Updated: 2025/12/02 01:40:35 by anruiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_bonus.h"

static void	fov_init(t_fov *f, t_data *data, t_minimap *map)
{
	f->lx = data->pos.dir_x - data->pos.plane_x;
	f->ly = data->pos.dir_y - data->pos.plane_y;
	f->rx = data->pos.dir_x + data->pos.plane_x;
	f->ry = data->pos.dir_y + data->pos.plane_y;
	f->rays = 200;
	f->i = 0;
	f->prev.pos_x = -1;
	f->prev.pos_y = -1;
	f->center.pos_x = map->pos_player.pos_x;
	f->center.pos_y = map->pos_player.pos_y;
	f->max_x = map->start_x + map->view_width - 0.0001;
	f->max_y = map->start_y + map->view_height - 0.0001;
}

static void	fov_compute_hit(t_data *d, t_minimap *map, t_fov *f)
{
	t_vec	dir;
	t_vec	hit;

	f->t = (double)f->i / (double)f->rays;
	f->dx = f->lx + (f->rx - f->lx) * f->t;
	f->dy = f->ly + (f->ry - f->ly) * f->t;
	dir.x = f->dx;
	dir.y = f->dy;
	cast_ray(d, dir, map->radius, &hit);
	f->hx = hit.x;
	f->hy = hit.y;
	if (f->hx < map->start_x)
		f->hx = map->start_x;
	if (f->hy < map->start_y)
		f->hy = map->start_y;
	if (f->hx > f->max_x)
		f->hx = f->max_x;
	if (f->hy > f->max_y)
		f->hy = f->max_y;
	f->hit.pos_x = map->pos_minimap_x
		+ (int)((f->hx - map->start_x) * map->scale);
	f->hit.pos_y = map->pos_minimap_y
		+ (int)((f->hy - map->start_y) * map->scale);
}

static void	fov_connect_segment(t_data *data, t_minimap *map, t_fov *f)
{
	t_thick_line	line;

	line.a = f->center;
	line.b = f->hit;
	line.color = 0xE7C46A;
	line.thickness = 1; // se ignora realmente
	draw_line(data, map, line);
}

void	fill_fov(t_data *data, t_minimap *map)
{
	t_fov	f;

	fov_init(&f, data, map);
	while (f.i <= f.rays)
	{
		fov_compute_hit(data, map, &f);
		fov_connect_segment(data, map, &f);
		f.i++;
	}
}
