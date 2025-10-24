/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:22:53 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/24 16:08:56 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	check_texture_path(char *path, t_data *data)
{
	int	fd;

	if (!path)
		ft_end(data, "Error : Missing texture path");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_end(data, "Error : Invalid texture path");
	close(fd);
}

void	check_all_texture_paths(t_data *data)
{
	check_texture_path(data->tex.no, data);
	check_texture_path(data->tex.so, data);
	check_texture_path(data->tex.we, data);
	check_texture_path(data->tex.ea, data);
}

void	free_map(char **map)
{
	int	j;

	j = 0;
	while (map[j])
		free(map[j++]);
	free(map);
}

void	ft_destroy_img(t_data *data)
{
	mlx_destroy_image(data->mlx, data->tex.no);
	mlx_destroy_image(data->mlx, data->tex.so);
	mlx_destroy_image(data->mlx, data->tex.we);
	mlx_destroy_image(data->mlx, data->tex.ea);
}

int	ft_end(t_data *data, char *msg)
{
	if (data->mlx)
		ft_destroy_img(data);
	if (data->map)
		free_map(data->map);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (msg)
		ft_printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
