/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:01:40 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/04 02:06:45 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3_H
#define CUB3_H

# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"

typedef struct s_data {
    void *mlx;      // puntero a mlx
    void *win;      // ventana
    int size_x;     // ancho de la ventana
    int size_y;     // alto de la ventana
    char **map;     // puntero al mapa (array de strings)
    
    // rutas de texturas
    char *no;
    char *so;
    char *we;
    char *ea;

    // colores
    int floor;
    int ceil;

    // posición y dirección del jugador
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
} t_data;

// PARSER
void	parse_scene(t_data *data, char **argv);
void	parse_textures(t_data *data, char *line, int *j);
void	parse_rgb(t_data *data, char *line, int *j);
void	check_elements(t_data *data);

// UTILS
int	ft_end(t_data *data, char *str);
char	skip_spaces(char *map, int *j);
int	is_empty_line(char *line);
void	append_error(char **msg, char *new_msg);

#endif