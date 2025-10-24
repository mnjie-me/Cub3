/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:14:23 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/24 16:34:58 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	ceil_floor_colors(t_data *data, int x)
{
	int	y;
	int	color;

	y = 0;
	while (y < IMG_H)
	{
		if (y < data->draw.start)
			color = data->colors.ceil;
		else if (y > data->draw.end)
			color = data->colors.floor;
		else
		{
			y++;
			continue ;
		}
		ft_mlx_pixel_put(&data->img, x, y, color);
		y++;
	}
}

void	load_hor_textures(t_data *data)
{
	int	w;
	int	h;

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

void	load_ver_textures(t_data *data)
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
	load_hor_textures(data);
}
