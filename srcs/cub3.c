/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:22:59 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/10 18:52:01 by mari-cruz        ###   ########.fr       */
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

void	init_data(t_data *data)
{
	data->colors.floor = -1;
	data->colors.ceil = -1;
	data->textures.no = NULL;
	data->textures.so = NULL;
	data->textures.we = NULL;
	data->textures.ea = NULL;
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
	raycast(&data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx,
			IMG_W, IMG_H, "./cub3");
	//mlx_hook(data.win, 17, 0, cleanup_and_exit, &data);
	mlx_loop(data.mlx);
	return (0);
}