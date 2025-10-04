/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:56:40 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/04 01:52:31 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	parse_map(char **map, t_data *data)
{
	(void)map;
	check_elements(data);
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
			continue;	
		}
		j = 0;
		skip_spaces(map[i], &j);
		if (ft_isalpha(map[i][j]))
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'W' || map[i][j] == 'E')
				parse_textures(data, map[i], &j);
			else if (map[i][j] == 'F' || map[i][j] == 'C')
				parse_rgb(data, map[i], &j);
		}
		else
			return;
		i++;
	}
}

char	**read_file(t_data *data, char **argv)
{
	char	*line;
	char 	**temp;
	int		fd;
	int		i;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_end(data, "Open file error\n");
	while ((line = get_next_line(fd)) != NULL)
	{
		temp = realloc(data->map, sizeof(char *) * (i + 1));
		if (!temp)
			ft_end(data, "Malloc failed");
		data->map = temp;
		data->map[i] = line;
		i++;
	}
	temp = realloc(data->map, sizeof(char *) * (i + 1));
	if (!temp)
		ft_end(data, "Malloc failed");
	data->map = temp;
	data->map[i] = NULL;
	close(fd);
	return (data->map);
}

void	parse_scene(t_data *data, char **argv)
{
	read_file(data, argv);
	parse_config(data->map, data);
	parse_map(data->map, data); // comprobar que tengo todos los elementos al principio de la función
}
