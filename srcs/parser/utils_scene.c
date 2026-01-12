/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruiz-d <anruiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:22:53 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/01/12 16:40:15 by anruiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	check_texture_path(char *path, t_data *data)
{
	int	fd;
	size_t	len;

	if (!path)
		ft_end(data, "Error : Missing texture path");
	len = ft_strlen(path);
	if (len < 4 || ft_strnstr(path, ".xpm", len) != (path + len - 4))
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
