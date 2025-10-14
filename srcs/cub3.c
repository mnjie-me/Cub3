/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:22:59 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/14 12:22:03 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

/* int cleanup_and_exit(t_data *data)
{
    if (data->map)
        free_map(data->map);
    if (data->mlx)
    {
        ft_destroy_img(data);
        mlx_destroy_window(data->mlx, data->win);
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    exit(0);
} */

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
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

void	init_data(t_data *data)
{
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
	load_textures(&data);
	render_loop(&data);
	//mlx_hook(data.win, 17, 0, cleanup_and_exit, &data);
	mlx_loop(data.mlx);
	return (0);
}
