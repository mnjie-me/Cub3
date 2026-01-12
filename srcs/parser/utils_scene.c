/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruiz-d <anruiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:22:53 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/01/12 15:48:25 by anruiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	check_texture_path(char *path, t_data *data, char *cordinate)
{
	int	fd;

	if (!path)
		ft_end(data, "Error : Missing texture path");
	if (ft_strncmp(path, cordinate, ft_strlen(cordinate)))
		ft_end(data, "Error : Missing texture path");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_end(data, "Error : Invalid texture path");
	close(fd);
}

void	check_all_texture_paths(t_data *data)
{
	check_texture_path(data->tex.no, data, "NO srcs/textures/NO.xpm");
	check_texture_path(data->tex.so, data, "EA srcs/textures/EA.xpm");
	check_texture_path(data->tex.we, data, "WE srcs/textures/WE.xpm");
	check_texture_path(data->tex.ea, data, "SO srcs/textures/SO.xpm");
}
