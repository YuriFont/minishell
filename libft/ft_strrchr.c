/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:37:15 by yufonten          #+#    #+#             */
/*   Updated: 2023/10/17 14:47:46 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len_s;

	len_s = ft_strlen(s);
	if (!s)
		return (NULL);
	while (len_s >= 0)
	{
		if (s[len_s] == c)
			return ((char *)(s + len_s));
		len_s--;
	}
	return (NULL);
}
