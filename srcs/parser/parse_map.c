/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:49:36 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/06 23:57:40 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	validate_map(t_data *data, char **copy, int x, int y)
{
	if (x < 0 || x >= data->size_x || y < 0 || y >= data->size_y)
		ft_end(data, "Error : Out of border");
	if (copy[y][x] == ' ')
		ft_end(data, "Error : Open border");
	if (ft_cmp(copy[y][x], "0NSWE"))
	{
		copy[y][x] = 'F';
		validate_map(data, copy, x + 1, y);
		validate_map(data, copy, x - 1, y);
		validate_map(data, copy, x, y + 1);
		validate_map(data, copy, x, y - 1);
	}
}

void	place_character(t_data *data, char **copy)
{
	int	x;
	int	y;

	check_character(data, copy);
	y = 0;
	while (copy[y])
	{
		x = 0;
		while (copy[y][x])
		{
			if (copy[y][x] == 'N' || copy[y][x] == 'S' ||
				copy[y][x] == 'W' || copy[y][x] == 'E')
			{
				check_direction(data, copy, &x, &y);
				check_position(data, &x, &y);	
			}
			x++;
			if (x > data->size_x)
				data->size_x = x;
		}
		y++;
	}
	data->size_y = y;
}

char	**extract_map(char **text, int start)
{
	char	**copy;
	int		count;
	int		j;

	count = start;
	while (text[count] && !is_empty_line(text[count]))
		count++;
	copy = malloc(sizeof(char *) * (count - start + 1));
	if (!copy)
		return (NULL);
	j = 0;
	while (text[start] && !is_empty_line(text[start]))
	{
		copy[j] = ft_strdup(text[start]);
		if (!copy[j])
		{
			free_copy(copy, &j);
			return (NULL);	
		}
		j++;
		start++;
	}
	copy[j] = NULL;
	return (copy);
}


void	check_map(t_data *data, char **map, int *i)
{
	char	**copy;

	copy = extract_map(map, *i);
	if (!copy)
		ft_end(data, "Error : Copy failed");
	place_character(data, copy);
	validate_map(data, copy, data->position.x, data->position.y);
	free_map(copy);
	data->map = extract_map(map, *i);
	if (!data->map)
		ft_end(data, "Error : data->map malloc failed");
}