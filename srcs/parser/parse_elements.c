/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:17:06 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/04 02:03:52 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	free_split(char **rgb)
{
	int	i;

	i = 0;
	if (!rgb)
		return ;
	while (rgb[i])
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
}

void check_elements(t_data *data)
{
    char *msg = NULL;

    if (!data->no)
		append_error(&msg, "Missing texture: NO\n");
    if (!data->so)
		append_error(&msg, "Missing texture: SO\n");
    if (!data->we)
		append_error(&msg, "Missing texture: WE\n");
    if (!data->ea)
		append_error(&msg, "Missing texture: EA\n");
    if (data->floor == -1)
		append_error(&msg, "Missing floor color\n");
    if (data->ceil == -1)
		append_error(&msg, "Missing ceiling color\n");
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
		perror("invalid RGB value 1");
	while (num[i])
	{
		if ((num[i] < '0' || num[i] > '9') && num[i] != '\n')
			perror("invalid RGB value 2");
		i++;
	}
	result = ft_atoi(num);
	if (result < 0 || result > 255)
		perror("invalid RGB value 3");
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
			ft_end(data, "Invalid RGB format");
		r = check_value(rgb[0]);
		g = check_value(rgb[1]);
		b = check_value(rgb[2]);
		if (id == 'F')
			data->floor = (r << 16) | (g << 8) | b;
		else if (id == 'C')
			data->ceil = (r << 16) | (g << 8) | b;
		free_split(rgb);
	}
	else
		ft_end(data, "Invalid RGB identifier");
}

void	parse_textures(t_data *data, char *line, int *j)
{
	char	id;

	id = line[*j];
	*j += 1;
	if (line[*j + 1] == ' ' &&
		((id == 'N' && line[*j] == 'O') ||
        (id == 'S' && line[*j] == 'O') ||
        (id == 'W' && line[*j] == 'E') ||
        (id == 'E' && line[*j] == 'A'))) // puede que aquí tenga que añadir "si hay un espacio despues"
	{
		(*j)++;
		skip_spaces(line, j);
		if (!line[*j])
			ft_end(data, "Missing texture path");
		if (id == 'N')
			data->no = ft_strdup(line + *j);
		else if (id == 'S')
			data->so = ft_strdup(line + *j);
		else if (id == 'W')
			data->we = ft_strdup(line + *j);
		else if (id == 'E')
			data->ea = ft_strdup(line + *j);	
	}
	else
		ft_end(data, "Invalid texture identifier");
}
