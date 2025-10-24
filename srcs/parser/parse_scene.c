/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:56:40 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/24 17:32:57 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	parse_map(char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	check_elements(data);
	while (map[i] && !ft_isdigit(map[i][j]))
	{
		i++;
		j = 0;
		while (map[i] && is_empty_line(map[i]))
			i++;
		if (!map[i])
			ft_end(data, "Error: No map found");
		skip_spaces(map[i], &j);
	}
	if (!map[i])
		ft_end(data, "Error: Invalid map");
	check_map(data, map, &i);
}

void	parse_config(char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		if (is_empty_line(map[i]))
		{
			i++;
			continue ;
		}
		j = 0;
		skip_spaces(map[i], &j);
		if (ft_isalpha(map[i][j]))
			check_identifier(data, map, &i, &j);
		else
		{
			i++;
			continue ;
		}
		i++;
	}
	check_all_texture_paths(data);
}

char	**read_file(t_data *data, char **argv)
{
	char	*line;
	int		fd;
	int		count;

	count = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_end(data, "Error: File could not be opened");
	while ((line = get_next_line(fd)) != NULL)
	{
		data->map = ft_realloc(data->map,
				sizeof(char *) * count, sizeof(char *) * (count + 1));
		if (!data->map)
			ft_end(data, "Error: Malloc failed");
		data->map[count++] = line;
	}
	data->map = ft_realloc(data->map,
			sizeof(char *) * count, sizeof(char *) * (count + 1));
	if (!data->map)
		ft_end(data, "Error: Malloc failed");
	data->map[count] = NULL;
	close(fd);
	return (data->map);
}

void	parse_scene(t_data *data, char **argv)
{
	read_file(data, argv);
	parse_config(data->map, data);
	parse_map(data->map, data);
	data->map[(int)data->pos.pos_y][(int)data->pos.pos_x] = '0';
}
