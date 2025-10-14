/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:01:40 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/14 12:42:40 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3_H
# define CUB3_H

# define IMG_W 1024
# define IMG_H 768

# ifndef M_PI
# define M_PI 3.14159265358979323846
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "libft.h"
# include "mlx.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_draw
{
	double	wall_height;
	int		start;
	int		end;
}t_draw;

typedef struct s_ray
{
	int		map_h;
	int		map_w;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	double	wall_x;
}t_ray;

typedef struct s_pos
{
    double  pos_x;
    double  pos_y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
} t_pos;

typedef struct s_colors
{
    int floor;
    int ceil; 
}t_colors;

typedef struct s_tex
{
    char *no;
    char *so;
    char *we;
    char *ea;
}t_tex;

typedef struct s_data
{
    void		*mlx;
    void		*win;
    char		**map;
    t_tex		tex;
	t_colors	colors;
    t_pos       pos;
	t_ray		ray;
	t_draw		draw;
	t_img		img;
	t_img		t[4];
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
void		check_position(t_data *data, char **copy, int *x, int *y);
int	        get_max_x(char **copy);
void	    expand_tabs(char **copy);
void        remove_newline(char **copy);
char 		*ft_strdup_trim(const char *s);

// ENGINE
void	raycast(t_data *data);
void	calculate_perp(t_data *data);
void	draw_wall(t_data *data, int x);
void 	load_textures(t_data *data);
void	draw_wall_column(t_data *data, int x);

// ENGINE UTILS
void	init_ray(t_data *data);
void	fill_gaps(char **map);
int		check_width(char **map, int row);
int		check_height(char **map);
void	img_pixel_put(t_img *img, int x, int y, int color);

#endif