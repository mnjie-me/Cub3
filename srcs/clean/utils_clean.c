/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:59:36 by ana               #+#    #+#             */
/*   Updated: 2025/12/13 02:17:00 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

int	close_window(t_data *data)
{
	if (data && data->mlx)
		destroy_images(data);
	if (data)
		free_textures(data);
	if (data && data->map)
		free_map(data->map);
	if (data && data->mlx && data->win)
		mlx_cleanup(data);
	exit(0);
}

void	reset(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	clear_image(t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < IMG_H)
	{
		x = 0;
		while (x < IMG_W)
		{
			reset(img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	destroy_images(t_data *data)
{
	int	i;

	if (!data || !data->mlx)
		return ;
	i = 0;
	while (i < 4)
	{
		if (data->t[i].img)
		{
			mlx_destroy_image(data->mlx, data->t[i].img);
			data->t[i].img = NULL;
		}
		i++;
	}
	if (data->img.img)
	{
		mlx_destroy_image(data->mlx, data->img.img);
		data->img.img = NULL;
	}
}

void	mlx_cleanup(t_data *data)
{
	if (!data)
		return ;
	if (data->mlx && data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->mlx)
		free(data->mlx);
	data->mlx = NULL;
}
