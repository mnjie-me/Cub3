/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 02:06:14 by ana               #+#    #+#             */
/*   Updated: 2025/12/13 02:18:54 by ana              ###   ########.fr       */
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

int	ft_end(t_data *data, char *msg)
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
