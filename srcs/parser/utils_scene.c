/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:22:53 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/12/12 23:00:03 by ana              ###   ########.fr       */
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
