/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruiz-d <anruiz-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:40:13 by anruiz-d          #+#    #+#             */
/*   Updated: 2025/11/24 17:00:32 by anruiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_bonus.h"

int cell_color(char c)
{
    if (c == '1')
        return (0x6E6E6E);
    if (c == ' ' || c == '\r' || c == '\t' || c == '\n')
        return (0x2A2A2A);
    return (0xEDEDED);
}

int	minimap_width(char **map)
{
	int		i;
	int		len;
	int		width;

	i = 0;
	len = 0;
	width = 0;
	while (map[i])
	{
		len = (int)ft_strlen(map[i]);
		if (len > width)
			width = len;
		i++;
	}
	return (width);
}
int	minimap_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void norm(double *dx, double *dy)
{
    double len;

    len = sqrt((*dx) * (*dx) + (*dy) * (*dy));
    if (len > 0.00001)
    {
        *dx /= len;
        *dy /= len;
    }
}

void put_pixel(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || y < 0 || x >= IMG_W || y >= IMG_H)
        return;
    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}
