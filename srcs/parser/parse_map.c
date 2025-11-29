/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:49:36 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/11/29 21:32:07 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	check_textures_before_map(t_data *data, char **copy)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (copy[i])
	{
		if (ft_strncmp(copy[i], "NO ", 3) == 0
			|| ft_strncmp(copy[i], "SO ", 3) == 0
			|| ft_strncmp(copy[i], "WE ", 3) == 0
			|| ft_strncmp(copy[i], "EA ", 3) == 0
			|| ft_strncmp(copy[i], "F ", 2) == 0
			|| ft_strncmp(copy[i], "C ", 2) == 0)
			n++;
		i++;
	}
	if (n != 6)
		ft_end(data, "Error : missing textures before map");
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
				check_position(data, copy, &x, &y);
			x++;
		}
		y++;
	}
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
	check_textures_before_map(data, copy);
	place_character(data, copy);
	validate_map(data, copy);
	free_map(copy);
	data->map = extract_map(map, *i);
	if (!data->map)
		ft_end(data, "Error : data->map malloc failed");
}
