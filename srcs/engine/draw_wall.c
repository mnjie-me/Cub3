/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:05:57 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/10 22:46:46 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	init_draw(t_data *data)
{
	data->draw.wall_height = 0;
	data->draw.start = 0;
	data->draw.end = 0;
}

/* void draw_floor_and_ceiling(t_data *data, int x)
{
    int y;
    double ray_dir_x0 = data->pos.dir_x - data->pos.plane_x;
    double ray_dir_y0 = data->pos.dir_y - data->pos.plane_y;
    double ray_dir_x1 = data->pos.dir_x + data->pos.plane_x;
    double ray_dir_y1 = data->pos.dir_y + data->pos.plane_y;

    for (y = data->draw.end + 1; y < IMG_H; y++)
    {
        // Distancia desde la cámara al suelo
        double p = y - IMG_H / 2.0;
        double row_dist = (0.5 * IMG_H) / p;

        // Interpolación de posición en el mundo
        double floor_x = data->pos.pos_x + row_dist * (ray_dir_x0 + (ray_dir_x1 - ray_dir_x0) * x / (double)IMG_W);
        double floor_y = data->pos.pos_y + row_dist * (ray_dir_y0 + (ray_dir_y1 - ray_dir_y0) * x / (double)IMG_W);

        // Aquí puedes usar un color fijo o textura
        int floor_color = data->colors.floor;
        int ceil_color = data->colors.ceil;

        img_pixel_put(&data->img, x, y, floor_color);
        img_pixel_put(&data->img, x, IMG_H - y - 1, ceil_color);
    }
} */

void draw_floor_and_ceiling(t_data *data, int x)
{
    int y;
    int floor_color = data->colors.floor;
    int ceil_color = data->colors.ceil;

    for (y = data->draw.end + 1; y < IMG_H; y++)
    {
        img_pixel_put(&data->img, x, y, floor_color);
        img_pixel_put(&data->img, x, IMG_H - y - 1, ceil_color);
    }
}


int	wall_orientation(t_data *data)
{
	// Paredes verticales (side = 0)
	if (data->ray.side == 0)
	{
		if (data->ray.ray_dir_x > 0)
			return (0xFF0000); // 🔴 Este
		else
			return (0x00FF00); // 🟢 Oeste
	}
	// Paredes horizontales (side = 1)
	else
	{
		if (data->ray.ray_dir_y > 0)
			return (0x0000FF); // 🔵 Sur
		else
			return (0xFFFF00); // 🟡 Norte
	}
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_wall(t_data *data, int x)
{
	int	y;

	y = 0;
	while (y < data->draw.start)
		img_pixel_put(&data->img, x, y++, data->colors.ceil);
	y = data->draw.start;
	while (y <= data->draw.end)
		img_pixel_put(&data->img, x, y++, wall_orientation(data));
	while (y < IMG_H)
		img_pixel_put(&data->img, x, y++, data->colors.floor);
	y++;
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
}


