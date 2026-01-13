/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:58:58 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/01/13 13:03:19 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	rotate_left(t_data *data, double rot_speed, double old_dir_x,
	double old_plane_x)
{
	data->pos.dir_x = data->pos.dir_x * cos(-rot_speed)
		- data->pos.dir_y * sin(-rot_speed);
	data->pos.dir_y = old_dir_x * sin(-rot_speed)
		+ data->pos.dir_y * cos(-rot_speed);
	data->pos.plane_x = data->pos.plane_x * cos(-rot_speed)
		- data->pos.plane_y * sin(-rot_speed);
	data->pos.plane_y = old_plane_x * sin(-rot_speed)
		+ data->pos.plane_y * cos(-rot_speed);
}

void	rotate_right(t_data *data, double rot_speed, double old_dir_x,
	double old_plane_x)
{
	data->pos.dir_x = data->pos.dir_x * cos(rot_speed)
		- data->pos.dir_y * sin(rot_speed);
	data->pos.dir_y = old_dir_x * sin(rot_speed)
		+ data->pos.dir_y * cos(rot_speed);
	data->pos.plane_x = data->pos.plane_x * cos(rot_speed)
		- data->pos.plane_y * sin(rot_speed);
	data->pos.plane_y = old_plane_x * sin(rot_speed)
		+ data->pos.plane_y * cos(rot_speed);
}

void	rotate_player(t_data *data, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->pos.dir_x;
	old_plane_x = data->pos.plane_x;
	if (data->keys.left)
		rotate_left(data, rot_speed, old_dir_x, old_plane_x);
	if (data->keys.right)
		rotate_right(data, rot_speed, old_dir_x, old_plane_x);
}

void	move_player_sideways(t_data *data, int key, double move_speed)
{
	double	new_x;
	double	new_y;

	if (key == A_KEY)
	{
		new_x = data->pos.pos_x - data->pos.plane_x * move_speed;
		new_y = data->pos.pos_y - data->pos.plane_y * move_speed;
		if (data->map[(int)(data->pos.pos_y)][(int)new_x] == '0')
			data->pos.pos_x = new_x;
		if (data->map[(int)new_y][(int)(data->pos.pos_x)] == '0')
			data->pos.pos_y = new_y;
	}
	else if (key == D_KEY)
	{
		new_x = data->pos.pos_x + data->pos.plane_x * move_speed;
		new_y = data->pos.pos_y + data->pos.plane_y * move_speed;
		if (data->map[(int)(data->pos.pos_y)][(int)new_x] == '0')
			data->pos.pos_x = new_x;
		if (data->map[(int)new_y][(int)(data->pos.pos_x)] == '0')
			data->pos.pos_y = new_y;
	}
}

void	move_player(t_data *data, int key, double move_speed)
{
	double	new_x;
	double	new_y;

	if (key == W_KEY)
	{
		new_x = data->pos.pos_x + data->pos.dir_x * move_speed;
		new_y = data->pos.pos_y + data->pos.dir_y * move_speed;
		if (data->map[(int)(data->pos.pos_y)][(int)new_x] == '0')
			data->pos.pos_x = new_x;
		if (data->map[(int)new_y][(int)(data->pos.pos_x)] == '0')
			data->pos.pos_y = new_y;
	}
	else if (key == S_KEY)
	{
		new_x = data->pos.pos_x - data->pos.dir_x * move_speed;
		new_y = data->pos.pos_y - data->pos.dir_y * move_speed;
		if (data->map[(int)(data->pos.pos_y)][(int)new_x] == '0')
			data->pos.pos_x = new_x;
		if (data->map[(int)new_y][(int)(data->pos.pos_x)] == '0')
			data->pos.pos_y = new_y;
	}
	else
		move_player_sideways(data, key, move_speed);
}
