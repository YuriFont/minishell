/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:45:27 by yufonten          #+#    #+#             */
/*   Updated: 2023/10/24 17:16:34 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	ptr_s1 = (unsigned char *)s1;
	ptr_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n && ptr_s1[i] && ptr_s2[i])
	{
		if (ptr_s1[i] != ptr_s2[i])
			return ((int)ptr_s1[i] - (int)ptr_s2[i]);
		i++;
	}
	if (i < n)
		return ((int)ptr_s1[i] - (int)ptr_s2[i]);
	return (0);
}
