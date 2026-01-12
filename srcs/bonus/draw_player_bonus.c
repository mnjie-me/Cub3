/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruiz-d <anruiz-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:43:51 by anruiz-d          #+#    #+#             */
/*   Updated: 2025/11/24 16:58:57 by anruiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_bonus.h"

void	draw_player(t_data *data, t_minimap *map)
{
	t_rect	r;

	r.start_x = map->pos_player.pos_x - 2;
	r.start_y = map->pos_player.pos_y - 2;
	r.width = 4;
	r.height = 4;
	r.color = 0xFF2B2B;
	r.y = -1;
	while (++r.y < r.height)
	{
		r.x = -1;
		while (++r.x < r.width)
			put_pixel(&data->img, r.start_x + r.x, r.start_y + r.y, r.color);
	}
}
