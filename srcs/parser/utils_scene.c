/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:22:53 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/14 11:43:28 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

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

int ft_end(t_data *data, char *msg)
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
