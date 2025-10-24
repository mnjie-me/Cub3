/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:55:00 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/24 16:08:00 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

int	get_max_x(char **copy)
{
	int	y;
	int	max;
	int	len;

	y = 0;
	max = 0;
	while (copy[y])
	{
		len = (int)ft_strlen(copy[y]);
		if (len > 0 && (copy[y][len - 1] == '\n'))
			len--;
		if (len > max)
			max = len;
		y++;
	}
	return (max);
}

void	remove_newline(char **copy)
{
	int	y;
	int	len;

	y = 0;
	while (copy[y])
	{
		len = (int)ft_strlen(copy[y]);
		if (len > 0 && copy[y][len - 1] == '\n')
			copy[y][len - 1] = '\0';
		y++;
	}
}

char	*add_chars(char *copy, int len)
{
	int		j;
	int		x;
	char	*new_line;

	x = 0;
	j = 0;
	new_line = malloc(len + 1);
	if (!new_line)
		return (NULL);
	while (copy[x])
	{
		if (copy[x] == '\t')
		{
			new_line[j++] = ' ';
			new_line[j++] = ' ';
			new_line[j++] = ' ';
			new_line[j++] = ' ';
		}
		else
			new_line[j++] = copy[x];
		x++;
	}
	new_line[j] = '\0';
	return (new_line);
}

void	expand_tabs(char **copy)
{
	int		y;
	int		x;
	int		len;
	char	*new_line;

	y = 0;
	while (copy[y])
	{
		len = 0;
		x = 0;
		while (copy[y][x])
		{
			if (copy[y][x] == '\t')
				len += 4;
			else
				len += 1;
			x++;
		}
		new_line = add_chars(copy[y], len);
		free(copy[y]);
		copy[y] = new_line;
		y++;
	}
}
