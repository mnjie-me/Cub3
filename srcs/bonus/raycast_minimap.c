/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruiz-d <anruiz-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:01:46 by anruiz-d          #+#    #+#             */
/*   Updated: 2025/12/02 01:36:05 by anruiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_bonus.h"

static void	ray_init(t_raycast *r, t_data *d, t_vec dir, int radius)
{
	r->start_x = d->pos.pos_x;
	r->start_y = d->pos.pos_y;
	r->direcction_x = dir.x;
	r->direcction_y = dir.y;
	r->step = 0.02;
	r->max_steps = radius * 60;
	norm(&r->direcction_x, &r->direcction_y);
}

static int	ray_step(t_raycast *r, t_data *d)
{
	t_vec	next;
	int		cell_x;
	int		cell_y;
	int		prev_x;
	int		prev_y;

	prev_x = (int)r->start_x;
	prev_y = (int)r->start_y;
	next.x = r->start_x + r->direcction_x * r->step;
	next.y = r->start_y + r->direcction_y * r->step;
	if (next.y < 0 || next.y >= minimap_height(d->map))
		return (0);
	cell_y = (int)next.y;
	if (next.x < 0 || next.x >= (int)ft_strlen(d->map[cell_y]))
		return (0);
	cell_x = (int)next.x;
	if (d->map[cell_y][cell_x] == '1')
		return (0);
	if (cell_x != prev_x && cell_y != prev_y)
	{
		if ((d->map[prev_y][cell_x] == '1')
			|| (d->map[cell_y][prev_x] == '1'))
			return (0);
	}
	r->start_x = next.x;
	r->start_y = next.y;
	return (1);
}

void	cast_ray(t_data *d, t_vec dir, int radius, t_vec *out)
{
	t_raycast	r;
	int			i;

	ray_init(&r, d, dir, radius);
	i = 0;
	while (i < r.max_steps)
	{
		if (!ray_step(&r, d))
			break ;
		i++;
	}
	out->x = r.start_x;
	out->y = r.start_y;
}
