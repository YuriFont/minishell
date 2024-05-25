/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:57:01 by yufonten          #+#    #+#             */
/*   Updated: 2023/10/27 17:43:12 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	s;
	size_t	d;
	size_t	sizedest;
	size_t	sizesrc;

	sizesrc = ft_strlen(src);
	if (dst == NULL && size == 0)
		return (sizesrc);
	d = ft_strlen(dst);
	sizedest = d;
	if (size <= sizedest)
		return (size + sizesrc);
	s = 0;
	while (src[s] && d + 1 < size)
	{
		dst[d] = src[s];
		s++;
		d++;
	}
	dst[d] = 0;
	return (sizedest + sizesrc);
}
