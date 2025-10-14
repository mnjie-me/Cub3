/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:23:20 by jcalon            #+#    #+#             */
/*   Updated: 2025/10/13 22:51:08 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char		*strd;
	size_t		i;

	i = 0;
	if (src == NULL)
		return (NULL);
	strd = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!strd)
		return (NULL);
	while (src[i] != '\0')
	{
		strd[i] = src[i];
		i++;
	}
	strd[i] = '\0';
	return (strd);
}
