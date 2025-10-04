/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:22:53 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/03 15:05:42 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

static void	clear_map(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

static void	ft_destroy_img(t_data *data)
{
	mlx_destroy_image(data->mlx, data->no);
	mlx_destroy_image(data->mlx, data->so);
	mlx_destroy_image(data->mlx, data->we);
	mlx_destroy_image(data->mlx, data->ea);
}

int ft_end(t_data *data, char *msg)
{
    if (data->mlx)
        ft_destroy_img(data);
    if (data->map)
        clear_map(data->map);
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    if (msg)
        ft_printf("%s\n", msg);
    exit(EXIT_FAILURE);
}


int	ft_close(t_data *data)
{
	ft_end(data, "Sure you don't want to play any more?");
	return (0);
}