/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalahaye <jalahaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:59:05 by jalahaye          #+#    #+#             */
/*   Updated: 2024/11/19 12:19:53 by jalahaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dst;
	size_t	x;

	dst = 0;
	x = 0;
	while (dest[dst] && dst < size)
		dst++;
	while (src[x] && size && dst + x < size - 1)
	{
		dest[dst + x] = src[x];
		x++;
	}
	if (dst < size)
		dest[dst + x] = 0;
	x = 0;
	while (src[x])
		x++;
	return (dst + x);
}
