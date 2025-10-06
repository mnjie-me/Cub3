/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:56:40 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/06 23:56:42 by mari-cruz        ###   ########.fr       */
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
		/* if (!is_map_line(map[i]))
		{
			printf("line : %c\n", map[i][j]);	
			ft_end(data, "Error: Invalid line");		
		} */
	}
	if (!map[i])
		ft_end(data, "Error: Invalid map");
	check_map(data, map, &i);	
}
// mirar aquí a ver si tengo que liberar algo despues de hacer strdup;
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
			check_identifier(data, map, &i, &j);
		else
		{
			i++;
			continue;
		}
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
		ft_end(data, "Error: File could not be opened");
	while ((line = get_next_line(fd)) != NULL)
	{
		temp = ft_realloc(data->map, sizeof(char *) * i, sizeof(char *) * (i + 1));
		if (!temp)
			ft_end(data, "Error: Malloc failed");
		data->map = temp;
		data->map[i] = line;
		i++;
	}
	temp = ft_realloc(data->map, sizeof(char *) * i, sizeof(char *) * (i + 1));
	if (!temp)
		ft_end(data, "Error: Malloc failed");
	data->map = temp;
	data->map[i] = NULL;
	close(fd);
	return (data->map);
}

void	parse_scene(t_data *data, char **argv)
{
	read_file(data, argv);
	parse_config(data->map, data);
	parse_map(data->map, data);
	free_map(data->map);
	data->map = NULL;
}
