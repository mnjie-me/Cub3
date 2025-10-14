/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:14:23 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/14 14:08:15 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"



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