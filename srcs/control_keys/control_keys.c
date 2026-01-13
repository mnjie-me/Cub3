/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruiz-d <anruiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:06:25 by anruiz-d          #+#    #+#             */
/*   Updated: 2026/01/13 15:06:48 by anruiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

int	key_release(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		data->keys.w = 0;
	else if (keycode == A_KEY)
		data->keys.a = 0;
	else if (keycode == S_KEY)
		data->keys.s = 0;
	else if (keycode == D_KEY)
		data->keys.d = 0;
	else if (keycode == LEFT_ARROW)
		data->keys.left = 0;
	else if (keycode == RIGHT_ARROW)
		data->keys.right = 0;
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		data->keys.w = 1;
	else if (keycode == A_KEY)
		data->keys.a = 1;
	else if (keycode == S_KEY)
		data->keys.s = 1;
	else if (keycode == D_KEY)
		data->keys.d = 1;
	else if (keycode == LEFT_ARROW)
		data->keys.left = 1;
	else if (keycode == RIGHT_ARROW)
		data->keys.right = 1;
	else if (keycode == ESC_KEY)
		close_window(data);
	return (0);
}
