/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalahaye <jalahaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:26:00 by jalahaye          #+#    #+#             */
/*   Updated: 2024/11/25 17:32:43 by jalahaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	x;

	x = 0;
	while (x < n)
	{
		if (*(unsigned const char *)(s1 + x) != *(unsigned const char *)(s2
				+ x))
			return (*(unsigned const char *)(s1 + x)
				- *(unsigned const char *)(s2 + x));
		x++;
	}
	return (0);
}
