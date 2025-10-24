/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:16:37 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/24 16:10:36 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	check_character(t_data *data, char **copy)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (copy[y])
	{
		x = 0;
		while (copy[y][x] && copy[y][x] != '\n')
		{
			skip_spaces(copy[y], &x);
			if (ft_cmp(copy[y][x], "01NSWE") == 1)
				ft_end(data, "Error : Wrong identifier");
			if (ft_cmp(copy[y][x], "NSWE") == 0)
				count++;
			x++;
		}
		y++;
	}
	if (count > 1)
		ft_end(data, "Error : Too many characters");
	if (count < 1)
		ft_end(data, "Error : Character not found");
}

void	check_plane(t_data *data)
{
	double	fov_angle;
	double	fov;

	fov_angle = 66.0 * (M_PI / 180.0);
	fov = tan(fov_angle / 2.0);
	data->pos.plane_x = -data->pos.dir_y * tan(fov / 2.0);
	data->pos.plane_y = data->pos.dir_x * tan(fov / 2.0);
}

void	check_position(t_data *data, char **copy, int *x, int *y)
{
	if (copy[*y][*x] == 'N')
	{
		data->pos.dir_x = 0;
		data->pos.dir_y = -1;
	}
	else if (copy[*y][*x] == 'S')
	{
		data->pos.dir_x = 0;
		data->pos.dir_y = 1;
	}
	else if (copy[*y][*x] == 'W')
	{
		data->pos.dir_x = -1;
		data->pos.dir_y = 0;
	}
	else if (copy[*y][*x] == 'E')
	{
		data->pos.dir_x = 1;
		data->pos.dir_y = 0;
	}
	data->pos.pos_x = (double)(*x) + 0.5;
	data->pos.pos_y = (double)(*y) + 0.5;
	check_plane(data);
	copy[*y][*x] = '0';
}

void	free_copy(char **copy, int *j)
{
	while (*j > 0)
		free(copy[--(*j)]);
	free(copy);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	if (line[i] != ' ' && line[i] != '1'
		&& line[i] != 'N' && line[i] != 'S'
		&& line[i] != 'E' && line[i] != 'W'
		&& line[i] != 'F' && line[i] != 'C')
		return (0);
	return (1);
}
