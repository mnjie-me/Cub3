/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 02:08:24 by ana               #+#    #+#             */
/*   Updated: 2025/12/13 02:08:47 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->colors.floor = -1;
	data->colors.ceil = -1;
	data->tex.no = NULL;
	data->tex.so = NULL;
	data->tex.we = NULL;
	data->tex.ea = NULL;
	data->map = NULL;
	data->pos.pos_x = 0;
	data->pos.pos_y = 0;
	data->pos.dir_x = 0;
	data->pos.dir_x = 0;
	data->pos.plane_x = 0;
	data->pos.plane_y = 0;
	data->keys.w = 0;
	data->keys.a = 0;
	data->keys.s = 0;
	data->keys.d = 0;
}
