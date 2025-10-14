/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:14:23 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/14 14:06:49 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= IMG_W || y < 0 || y >= IMG_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static unsigned int	get_tex_color(t_img *tex, int tx, int ty)
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

void draw_wall_pixels(t_data *data, t_img *tex, int x)
{
    int y;
    int tex_x;
    int tex_y;
    double step;
    double tex_pos;

    if (data->ray.side == 0)
        tex_x = (int)(data->ray.wall_x * (double)(tex->width - 1));
    else
        tex_x = (int)((1.0 - data->ray.wall_x) * (double)(tex->width - 1));
    step = (double)tex->height / data->draw.wall_height;
    tex_pos = (data->draw.start - IMG_H / 2.0 + data->draw.wall_height / 2.0) * step;
    y = data->draw.start;
    while (y < data->draw.end)
    {
        tex_y = (int)tex_pos;
        if (tex_y >= tex->height)
            tex_y = tex->height - 1;
        if (tex_y < 0)
            tex_y = 0;
        tex_pos += step;
        unsigned int color = get_tex_color(tex, tex_x, tex_y);
        if (data->ray.side == 1)
            color = (color >> 1) & 0x7F7F7F;
        my_mlx_pixel_put(&data->img, x, y, color);
        y++;
    }
}

void draw_wall_column(t_data *data, int x)
{
    t_img *tex;

    if (data->ray.side == 0)
    {
        if (data->ray.ray_dir_x > 0)
            tex = &data->t[3]; // Este es E
        else
            tex = &data->t[2]; // Este es W
    }
    else
    {
        if (data->ray.ray_dir_y > 0)
            tex = &data->t[1]; // Este es S
        else
            tex = &data->t[0]; // Este es N
    }
    if (!tex || !tex->img)
        return;
    if (data->ray.side == 0)
        data->ray.wall_x = data->pos.pos_y + data->ray.perp_wall_dist * data->ray.ray_dir_y;
    else
        data->ray.wall_x = data->pos.pos_x + data->ray.perp_wall_dist * data->ray.ray_dir_x;
    data->ray.wall_x -= floor(data->ray.wall_x);
    draw_wall_pixels(data, tex, x);
}

void load_textures(t_data *data)
{
	int	w;
	int	h;
	
	data->t[0].img = mlx_xpm_file_to_image(data->mlx, data->tex.no, &w, &h);
	data->t[0].addr = mlx_get_data_addr(data->t[0].img,
		&data->t[0].bpp, &data->t[0].line_len, &data->t[0].endian);
	data->t[0].width = w;
	data->t[0].height = h;
	data->t[1].img = mlx_xpm_file_to_image(data->mlx, data->tex.so, &w, &h);
	data->t[1].addr = mlx_get_data_addr(data->t[1].img,
		&data->t[1].bpp, &data->t[1].line_len, &data->t[1].endian);
	data->t[1].width = w;
	data->t[1].height = h;
	data->t[2].img = mlx_xpm_file_to_image(data->mlx, data->tex.we, &w, &h);
	data->t[2].addr = mlx_get_data_addr(data->t[2].img,
		&data->t[2].bpp, &data->t[2].line_len, &data->t[2].endian);
	data->t[2].width = w;
	data->t[2].height = h;
	data->t[3].img = mlx_xpm_file_to_image(data->mlx, data->tex.ea, &w, &h);
	data->t[3].addr = mlx_get_data_addr(data->t[3].img,
		&data->t[3].bpp, &data->t[3].line_len, &data->t[3].endian);
	data->t[3].width = w;
	data->t[3].height = h;
}