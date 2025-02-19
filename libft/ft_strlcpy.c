/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalahaye <jalahaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:45:59 by jalahaye          #+#    #+#             */
/*   Updated: 2024/11/19 14:34:12 by jalahaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	x;

	x = 0;
	if (size > 0)
	{
		while (src[x] && x < (size - 1))
		{
			dst[x] = src[x];
			x++;
		}
		dst[x] = 0;
	}
	while (src[x])
		x++;
	return (x);
}
