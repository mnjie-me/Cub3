/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:05:16 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/09 17:27:18 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	raycast(t_data *data)
{
	int	map_y;
	int	map_x;
	int	step_y;
	int step_x;

	map_x = (int)data->position.pos_x;
	map_y = (int)data->position.pos_y;
	printf("positon y : %d, position x : %d\n", map_y, map_x);

	
	delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
	delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
	
}