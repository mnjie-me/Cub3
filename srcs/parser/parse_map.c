/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruiz-d <anruiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:49:36 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/02/07 17:48:48 by anruiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

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

static	void	check_textures_before_map(t_data *data, char **text)
{
	int		i;
	char	*s;

	i = 0;
	while (text[i])
	{
		s = text[i];
		while (*s == ' ' || *s == '\t' || *s == '\n')
			s++;
		if (*s == '1')
			break ;
		i++;
	}
	while (text[i])
	{
		s = text[i];
		while (*s == ' ' || *s == '\t' || *s == '\n')
			s++;
		if (!ft_strncmp(s, "NO ", 3) || !ft_strncmp(s, "SO ", 3)
			|| !ft_strncmp(s, "WE ", 3) || !ft_strncmp(s, "EA ", 3)
			|| !ft_strncmp(s, "F ", 2) || !ft_strncmp(s, "C ", 2))
			ft_end(data, NULL,"Error: texture found after map");
		i++;
	}
}

void	check_map(t_data *data, char **map, int *i)
{
	char	**copy;

	check_textures_before_map(data, map);
	copy = extract_map(map, *i);
	if (!copy)
		ft_end(data, NULL,"Error : Copy failed");
	place_character(data, copy);
	validate_map(data, copy);
	free_map(copy);
	data->map = extract_map(map, *i);
	if (!data->map)
		ft_end(data, NULL,"Error : data->map malloc failed");
}
