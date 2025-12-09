/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:22:53 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/12/09 19:00:12 by ana              ###   ########.fr       */
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

void	free_textures(t_data *data)
{
	if (!data)
		return ;
	free(data->tex.no);
	free(data->tex.so);
	free(data->tex.we);
	free(data->tex.ea);
	data->tex.no = NULL;
	data->tex.so = NULL;
	data->tex.we = NULL;
	data->tex.ea = NULL;
}

void destroy_images(t_data *data)
{
    int i;

    if (!data || !data->mlx)
        return;
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

void mlx_cleanup(t_data *data)
{
    if (!data)
        return;
    if (data->mlx && data->win)
    {
        mlx_destroy_window(data->mlx, data->win);
        data->win = NULL;
    }
	#ifdef IS_MAC
		(void)data;
	#else
		if (data->mlx)
			mlx_destroy_display(data->mlx);
		if (data->mlx)
			free(data->mlx);
		data->mlx = NULL;
	#endif
}

int     ft_end(t_data *data, char *msg)
{
    if (data && data->mlx)
        destroy_images(data);
    if (data)
        free_textures(data);
    if (data && data->map)
        free_map(data->map);
    if (data && data->mlx)
        mlx_cleanup(data);
    if (msg)
        ft_printf("%s\n", msg);
    exit(EXIT_FAILURE);
}
