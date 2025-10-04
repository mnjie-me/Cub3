/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:22:59 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/04 01:21:07 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	init_data(t_data *data)
{
	data->floor = -1;
	data->ceil = -1;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->map = NULL;
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
		basic_error("Error, write : ./cub3 MAP.cub");
	init_data(&data);
    parse_scene(&data, argv);
	data.mlx = mlx_init();
    data.size_x = 1024;
    data.size_y = 768;
	data.win = mlx_new_window(data.mlx,
			data.size_x, data.size_y, "./cub3");
	mlx_loop(data.mlx);
	return (0);
}