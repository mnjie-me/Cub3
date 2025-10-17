/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:17:06 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/17 13:57:14 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void check_elements(t_data *data)
{
    char *msg = NULL;

    if (!data->tex.no)
		append_error(&msg, "Error: Missing texture: NO");
    if (!data->tex.so)
		append_error(&msg, "Error: Missing texture: SO");
    if (!data->tex.we)
		append_error(&msg, "Error: Missing texture: WE");
    if (!data->tex.ea)
		append_error(&msg, "Error: Missing texture: EA");
    if (data->colors.floor == -1)
		append_error(&msg, "Error: Missing floor color");
    if (data->colors.ceil == -1)
		append_error(&msg, "Error: Missing ceiling color");
    if (msg)
        ft_end(data, msg);
}

int	check_value(char *num)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (!num)
		perror("Error: RGB value does not exist");
	while (num[i])
	{
		if ((num[i] < '0' || num[i] > '9') && num[i] != '\n')
			perror("Error: Invalid RGB value");
		i++;
	}
	result = ft_atoi(num);
	if (result < 0 || result > 255)
		perror("Error: RGB value out of range");
	return (result);
}

void	parse_rgb(t_data *data, char *line, int *j)
{
	char	id;
	char	**rgb;
	int		r;
	int		g;
	int		b;
	
	id = line[*j];
	if (line[*j + 1] == ' ')
	{
		(*j)++;
		skip_spaces(line, j);
		rgb = ft_split(line + *j, ',');
		if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
			ft_end(data, "Error: Invalid RGB format");
		r = check_value(rgb[0]);
		g = check_value(rgb[1]);
		b = check_value(rgb[2]);
		if (id == 'F')
			data->colors.floor = (r << 16) | (g << 8) | b;
		else if (id == 'C')
			data->colors.ceil = (r << 16) | (g << 8) | b;
		free_split(rgb);
	}
	else
		ft_end(data, "Error: Invalid RGB identifier");
}

void	parse_textures(t_data *data, char *line, int *j)
{
	char	id;

	id = line[*j];
	*j += 1;
	if (line[*j + 1] == ' ' && ((id == 'N' && line[*j] == 'O')
			|| (id == 'S' && line[*j] == 'O') || (id == 'W'
			&& line[*j] == 'E') || (id == 'E' && line[*j] == 'A')))
	{
		(*j)++;
		skip_spaces(line, j);
		if (!line[*j])
			ft_end(data, "Error: Missing texture path");
		if (id == 'N')
			data->tex.no = ft_strdup_trim(line + *j);
		else if (id == 'S')
			data->tex.so = ft_strdup_trim(line + *j);
		else if (id == 'W')
			data->tex.we = ft_strdup_trim(line + *j);
		else if (id == 'E')
			data->tex.ea = ft_strdup_trim(line + *j);	
	}
	else
		ft_end(data, "Error: Invalid texture identifier");
}

void	check_identifier(t_data *data, char **map, int *i, int *j)
{
	static int	flags[6];
	int			id;

	id = -1;
	if (map[*i][*j] == 'N' && map[*i][*j + 1] == 'O')
		id = 0;
	else if (map[*i][*j] == 'S' && map[*i][*j + 1] == 'O')
		id = 1;
	else if (map[*i][*j] == 'W' && map[*i][*j + 1] == 'E')
		id = 2;
	else if (map[*i][*j] == 'E' && map[*i][*j + 1] == 'A')
		id = 3;
	else if (map[*i][*j] == 'F')
		id = 4;
	else if (map[*i][*j] == 'C')
		id = 5;
	else
		ft_end(data, "Error : Wrong identifier");
	if (flags[id] == 1)
		ft_end(data, "Error : Duplicate identifier");
	flags[id] = 1;
	if (id == 4 || id == 5)
		parse_rgb(data, map[*i], j);
	else
		parse_textures(data, map[*i], j);
}

