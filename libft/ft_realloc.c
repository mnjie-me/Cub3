/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:03:30 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/10/06 17:03:35 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	min_size;
	size_t	i;
	unsigned char	*src;
	unsigned char	*dst;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (!ptr)
		return (new_ptr);
	src = (unsigned char *)ptr;
	dst = (unsigned char *)new_ptr;
	min_size = old_size < new_size ? old_size : new_size;
	i = 0;
	while (i < min_size)
	{
		dst[i] = src[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}