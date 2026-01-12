/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:03:30 by mari-cruz         #+#    #+#             */
/*   Updated: 2025/12/13 05:06:43 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void			*new_ptr;
	size_t			min_size;
	size_t			i;
	unsigned char	*src;
	unsigned char	*dst;

	if (new_size == 0)
		return (free(ptr), NULL);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (!ptr)
		return (new_ptr);
	src = (unsigned char *)ptr;
	dst = (unsigned char *)new_ptr;
	if (old_size < new_size)
		min_size = old_size;
	else
		min_size = new_size;
	i = -1;
	while (++i < min_size)
		dst[i] = src[i];
	return (free(ptr), new_ptr);
}
