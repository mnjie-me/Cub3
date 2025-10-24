/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:06:26 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/24 16:14:47 by mnjie-me         ###   ########.fr       */
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
	char	*tmp;

	if (*msg)
	{
		tmp = *msg;
		*msg = ft_strjoin(*msg, new_msg);
		free(tmp);
	}
	else
		*msg = ft_strdup(new_msg);
}

char	*ft_strdup_trim(const char *s)
{
	size_t	start;
	size_t	end;
	char	*dup;
	size_t	len;

	start = 0;
	if (!s)
		return (NULL);
	while (s[start] && (s[start] == ' ' || s[start] == '\t'))
		start++;
	end = start;
	while (s[end] && s[end] != '\n')
		end++;
	while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t'))
		end--;
	len = end - start;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	memcpy(dup, s + start, len);
	dup[len] = '\0';
	return (dup);
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
