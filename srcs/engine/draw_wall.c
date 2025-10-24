/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:05:57 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/24 16:52:34 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	ft_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= IMG_W || y < 0 || y >= IMG_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_tex_color(t_img *tex, int tx, int ty)
{
	char	*dst;

	if (!tex || !tex->addr)
		return (0);
	if (tx < 0)
		tx = 0;
	if (ty < 0)
		ty = 0;
	if (tx >= tex->width)
		tx = tex->width - 1;
	if (ty >= tex->height)
		ty = tex->height - 1;
	dst = tex->addr + (ty * tex->line_len + tx * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

void	draw_wall_pixels(t_data *data, t_img *tex, int x)
{
	int		y;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;

	if (data->ray.side == 0)
		tex_x = (int)(data->ray.wall_x * (double)(tex->width - 1));
	else
		tex_x = (int)((1.0 - data->ray.wall_x) * (double)(tex->width - 1));
	step = (double)tex->height / data->draw.wall_height;
	tex_pos = (data->draw.start - IMG_H / 2.0
			+ data->draw.wall_height / 2.0) * step;
	y = data->draw.start;
	while (y < data->draw.end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		ft_mlx_pixel_put(&data->img, x, y,
			color_and_shade(data, tex, tex_x, tex_y));
		y++;
	}
}

void	draw_wall_column(t_data *data, int x)
{
	t_img	*tex;

	if (data->ray.side == 0)
	{
		if (data->ray.ray_dir_x > 0)
			tex = &data->t[3];
		else
			tex = &data->t[2];
	}
	else
	{
		if (data->ray.ray_dir_y > 0)
			tex = &data->t[1];
		else
			tex = &data->t[0];
	}
	if (!tex || !tex->img)
		return ;
	draw_wall_pixels(data, tex, x);
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
		data->ray.wall_x = data->pos.pos_y
			+ data->ray.perp_wall_dist * data->ray.ray_dir_y;
	else
		data->ray.wall_x = data->pos.pos_x
			+ data->ray.perp_wall_dist * data->ray.ray_dir_x;
	data->ray.wall_x -= floor(data->ray.wall_x);
}
