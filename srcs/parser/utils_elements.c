/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:06:26 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/06 15:46:22 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	free_split(char **rgb)
{
	int	i;

	i = 0;
	if (!rgb)
		return ;
	while (rgb[i])
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
}

void	append_error(char **msg, char *new_msg)
{
    char *tmp;

    if (*msg)
    {
        tmp = *msg;
        *msg = ft_strjoin(*msg, new_msg);
        free(tmp);
    }
    else
        *msg = ft_strdup(new_msg);
}

char	skip_spaces(char *map, int *j)
{
	while (map[*j] == ' ' || map[*j] == '\t')
		(*j)++;
	return (map[*j]);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}