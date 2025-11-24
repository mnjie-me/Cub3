/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruiz-d <anruiz-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:22:59 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/11/09 00:57:06 by anruiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

int close_window(t_data *data)
{
    if (data->win)
        mlx_destroy_window(data->mlx, data->win);
    exit(0);
    return (0);
}

int key_release(int keycode, t_data *data)
{
    if (keycode == W_KEY)
        data->keys.w = 0;
    else if (keycode == A_KEY)
        data->keys.a = 0;
    else if (keycode == S_KEY)
        data->keys.s = 0;
    else if (keycode == D_KEY)
        data->keys.d = 0;
    return (0);
}


int key_press(int keycode, t_data *data)
{
    if (keycode == W_KEY)
        data->keys.w = 1;
    else if (keycode == A_KEY)
        data->keys.a = 1;
    else if (keycode == S_KEY)
        data->keys.s = 1;
    else if (keycode == D_KEY)
        data->keys.d = 1;
    else if (keycode == ESC_KEY)
        close_window(data);
    return (0);
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

int render_loop(t_data *data)
{
    clear_image(&data->img);

    double move_speed = 0.1;
    double rot_speed = 0.05;

    if (data->keys.w)
        move_player(data, W_KEY, move_speed);
    if (data->keys.s)
        move_player(data, S_KEY, move_speed);
    if (data->keys.a || data->keys.d)
        rotate_player(data, rot_speed);

    raycast(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    return (0);
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->colors.floor = -1;
	data->colors.ceil = -1;
	data->tex.no = NULL;
	data->tex.so = NULL;
	data->tex.we = NULL;
	data->tex.ea = NULL;
	data->map = NULL;
	data->pos.pos_x = 0;
	data->pos.pos_y = 0;
	data->pos.dir_x = 0;
	data->pos.dir_x = 0;
	data->pos.plane_x = 0;
	data->pos.plane_y = 0;
	data->keys.w = 0;
	data->keys.a = 0;
	data->keys.s = 0;
	data->keys.d = 0;
}

static void	basic_error(char *str)
{
	ft_printf("%s\n", str);
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
    t_data  data;
    
	if (argc != 2 || ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))
    != (argv[1] + ft_strlen(argv[1]) - 4))
        basic_error("Error, write: ./cub3 SCENE.cub");
    init_data(&data);
    parse_scene(&data, argv);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, IMG_W, IMG_H, "./cub3");
	data.img.img = mlx_new_image(data.mlx, IMG_W, IMG_H);
	data.img.addr = mlx_get_data_addr(data.img.img,
			&data.img.bpp, &data.img.line_len, &data.img.endian);
	load_ver_textures(&data);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop_hook(data.mlx, render_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}
