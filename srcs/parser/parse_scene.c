/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruiz-d <anruiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:56:40 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/02/07 17:50:04 by anruiz-d         ###   ########.fr       */
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
			ft_end(data, NULL,"Error: No map found");
		skip_spaces(map[i], &j);
	}
	if (!map[i])
		ft_end(data, NULL, "Error: Invalid map");
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
		ft_end(data, NULL, "Error: File could not be opened");
	line = get_next_line(fd);
	while (line)
	{
		data->map = ft_realloc(data->map,
				sizeof(char *) * count, sizeof(char *) * (count + 1));
		if (!data->map)
			ft_end(data, NULL, "Error: Malloc failed");
		data->map[count++] = line;
		line = get_next_line(fd);
	}
	data->map = ft_realloc(data->map,
			sizeof(char *) * count, sizeof(char *) * (count + 1));
	if (!data->map)
		ft_end(data, NULL, "Error: Malloc failed");
	data->map[count] = NULL;
	close(fd);
	return (data->map);
}

void	parse_scene(t_data *data, char **argv)
{
	char	**text;

	text = read_file(data, argv);
	parse_config(text, data);
	parse_map(text, data);
	free_map(text);
	data->map[(int)data->pos.pos_y][(int)data->pos.pos_x] = '0';
}
