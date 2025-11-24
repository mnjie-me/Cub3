/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines_fov.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruiz-d <anruiz-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:56:19 by anruiz-d          #+#    #+#             */
/*   Updated: 2025/11/24 17:04:35 by anruiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_bonus.h"

void	draw_line(t_img *img, t_posminimap a, t_posminimap b, int color)
{
	int   steps;
	double x;
	double y;
	double step_x;
	double step_y;

	x = a.pos_x;
	y = a.pos_y;
	steps = abs(b.pos_x - a.pos_x);
	if (steps < abs(b.pos_y - a.pos_y))
		steps = abs(b.pos_y - a.pos_y);
	if (steps == 0)
	{
		put_pixel(img, a.pos_x, a.pos_y, color);
		return ;
	}
	step_x = (b.pos_x - a.pos_x) / (double)steps;
	step_y = (b.pos_y - a.pos_y) / (double)steps;
	while (steps-- >= 0)
	{
		put_pixel(img, (int)x, (int)y, color);
		x += step_x;
		y += step_y;
	}
}

void	line_thick(t_img *img, t_thick_line l)
{
	int		half;
	int		i;
	int		j;
	t_posminimap	origin;
	t_posminimap	dest;

	half = l.thickness / 2;
	i = -half;
	while (i++ <= half)
	{
		j = -half;
		while (j++ <= half)
		{
			if (i * i + j * j > half * half)
			{
				j++;
				continue ;
			}
			origin.pos_x = l.a.pos_x + i;
			origin.pos_y = l.a.pos_y + j;
			dest.pos_x = l.b.pos_x + i;
			dest.pos_y = l.b.pos_y + j;
			draw_line(img, origin, dest, l.color);
		}
	}
}
