/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:16:37 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/08 16:06:21 by mari-cruz        ###   ########.fr       */
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
			{
				printf("%c\n", copy[y][x]);	
				ft_end(data, "Error : Wrong character identifier");
			}
			if (ft_cmp(copy[y][x], "NSWE") == 0)
				count++;
			x++;
		}
		y++;
	}
	if (count > 1)
		ft_end(data, "Error : More than one character");
}

void	check_direction(t_data *data, char **copy, int *x, int *y)
{
	if (copy[*y][*x] == 'N')
	{
		data->position.dir_x = 1;
		data->position.dir_y = 0;
	}
	else if (copy[*y][*x] == 'S')
	{
		data->position.dir_x = -1;
		data->position.dir_y = 0;	
	}
	else if (copy[*y][*x] == 'W')
	{
		data->position.dir_x = 0;
		data->position.dir_y = -1;	
	}
	else if (copy[*y][*x] == 'E')
	{
		data->position.dir_x = 0;
		data->position.dir_y = 1;
	}
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