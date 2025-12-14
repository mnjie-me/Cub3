/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:18:03 by anruiz-d          #+#    #+#             */
/*   Updated: 2025/12/13 22:28:30 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3_BONUS_H
# define CUB3_BONUS_H

# include "cub3.h"

typedef struct s_posminimap
{
	int				pos_x;
	int				pos_y;
}	t_posminimap;

typedef struct s_minimap
{
	int				map_width;	// ancho del mapa en celdas
	int				map_height;	// alto del mapa en celdas
	int				start_x; // vision de las celdas alrededor del jugador
	int				start_y;
	int				pos_minimap_x;//coordenadas minimapa dentro de la pantalla
	int				pos_minimap_y;
	int				radius;		// celdas visibles alrededor del jugador
	int				view_width;		// tamaño del mapa en celdas 
	int				view_height;
	int				size_mmap;	//tamaño del minimapa
	int				scale;	// escala en pixeles de cada celda en el minimapa
	int				width;		// ancho del mapa en pixeles pantalla
	int				height;
	t_posminimap	pos_player;
}	t_minimap;

typedef enum e_layer
{
	BACKGROUND,
	BORDER
}	t_layer;

typedef struct s_rect
{
	int				x;
	int				y;
	int				width;
	int				height;
	int				color;
	int				start_x;
	int				start_y;
}	t_rect;

typedef struct s_tile
{
	int				x;
	int				y;
	char			cell;
}	t_tile;

typedef struct s_thick_line
{
	t_posminimap	a;
	t_posminimap	b;
	int				color;
	double			thickness;
}	t_thick_line;

typedef struct s_fov
{
	double			lx;
	double			ly;
	double			rx;
	double			ry;
	int				rays;
	int				i;
	double			t;
	double			dx;
	double			dy;
	double			hx;
	double			hy;
	double			max_x;
	double			max_y;
	t_posminimap	center;
	t_posminimap	prev;
	t_posminimap	hit;
}	t_fov;

typedef struct s_vec
{
	double			x;
	double			y;
}	t_vec;

typedef struct s_raycast
{
	double			start_x;
	double			start_y;
	double			direcction_x;
	double			direcction_y;
	double			step;
	int				max_steps;
}	t_raycast;

void	draw_minimap(t_data *data);
void	draw_short_map(t_data *data, t_minimap *map);
void	put_pixel(t_img *img, int x, int y, int color);
int		cell_color(char c);
int		minimap_width(char **map);
int		minimap_height(char **map);
void	norm(double *dx, double *dy);
void	draw_line(t_data *data, t_minimap *map, t_thick_line l);
void	cast_ray(t_data *data, t_vec dir, int radius, t_vec *out);
void	fill_fov(t_data *data, t_minimap *map);
void	draw_player(t_data *data, t_minimap *map);

#endif
