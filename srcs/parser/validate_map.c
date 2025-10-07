/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:03:59 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/07 22:13:39 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	flood_fill(t_data *data, char **copy, int x, int y)
{
	if (x < 0 || x >= data->size_x)
		ft_end(data, "Error : Out of border");
	if (x < 0 || x >= (int)ft_strlen(copy[y]))
		ft_end(data, "Error : Open border");
	if (copy[y][x] == ' ')
		ft_end(data, "Error : Open border");
	if (ft_cmp(copy[y][x], "0NSWE"))
	{
		copy[y][x] = 'F';
		flood_fill(data, copy, x + 1, y);
		flood_fill(data, copy, x - 1, y);
		flood_fill(data, copy, x, y + 1);
		flood_fill(data, copy, x, y - 1);
	}
}

static void	validate_column_edges(t_data *data, char **copy, int x, int total_rows)
{
	int	start;
	int	end;

	start = 0;
	while (copy[start] && (x >= (int)ft_strlen(copy[start]) || copy[start][x] == ' '))
		start++;
	end = total_rows - 1;
	while (end >= 0 && (x >= (int)ft_strlen(copy[end]) || copy[end][x] == ' '))
		end--;
	if (start > end)
		ft_end(data, "Error: Empty column in map");
	if (copy[start][x] != '1' || copy[end][x] != '1')
		ft_end(data, "Error: Map out of borders (columns)");
}

void	validate_columns(t_data *data, char **copy)
{
	int	x;
	int	total_rows;
	int	max_x;

	total_rows = 0;
	while (copy[total_rows])
		total_rows++;
	max_x = get_max_x(copy);
	x = 0;
	while (x < max_x)
	{
		validate_column_edges(data, copy, x, total_rows);
		x++;
	}
}

void	validate_rows(t_data *data, char **copy)
{
	int	y;
	int	start;
	int	end;

	y = 0;
	while (copy[y])
	{
		start = 0;
		while (copy[y][start] && (copy[y][start] == ' ' || copy[y][start] == '\t'))
			start++;
		end = (int)ft_strlen(copy[y]) - 1;
		while (end >= 0 && (copy[y][end] == ' ' || copy[y][end] == '\t' || copy[y][end] == '\n'))
			end--;
		if (start > end)
			ft_end(data, "Error: Empty line in map");
		if (copy[y][start] != '1' || copy[y][end] != '1')
			ft_end(data, "Error: Map out of borders (rows)");
		y++;
	}
}

void	validate_map(t_data *data, char **copy)
{
	validate_rows(data, copy);
	validate_columns(data, copy);
	flood_fill(data, copy, data->position.x, data->position.y);
}