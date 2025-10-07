/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:01:40 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/07 21:45:20 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3_H
#define CUB3_H

# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"

typedef struct s_position
{
    double x;
    double y;
    double dir_x;
    double dir_y;
} t_position;

typedef struct s_colors
{
    int floor;
    int ceil; 
}t_colors;

typedef struct s_textures
{
    char *no;
    char *so;
    char *we;
    char *ea;
}t_textures;

typedef struct s_data
{
    void		*mlx;
    void		*win;
    int			size_x;
    int			size_y;
    char		**map;
    t_textures	textures;
	t_colors	colors;
    t_position  position;
} t_data;

// PARSER
void	parse_scene(t_data *data, char **argv);
void	parse_textures(t_data *data, char *line, int *j);
void	parse_rgb(t_data *data, char *line, int *j);
void	check_identifier(t_data *data, char **map, int *i, int *j);
void	check_elements(t_data *data);
void	check_map(t_data *data, char **map, int *i);
void	validate_map(t_data *data, char **copy);

// PARSER UTILS
void		ft_destroy_img(t_data *data);
int			ft_end(t_data *data, char *str);
char		skip_spaces(char *map, int *j);
int			is_empty_line(char *line);
void		append_error(char **msg, char *new_msg);
void		free_split(char **rgb);
int			is_map_line(char *line);
void		free_map(char **map);
void		free_copy(char **copy, int *j);
void		check_character(t_data *data, char **copy);
void		check_direction(t_data *data, char **copy, int *x, int *y);
void		check_position(t_data *data, int *x, int *y);
int	        get_max_x(char **copy);

#endif