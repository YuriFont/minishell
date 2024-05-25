/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:36:52 by yufonten          #+#    #+#             */
/*   Updated: 2024/05/25 16:36:52 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	aconts1(char *r, char const*s1)
{
	size_t	j;

	j = 0;
	while (s1[j] != '\0')
	{
		r[j] = s1[j];
		j++;
	}
	return (j);
}

char	*ft_strjoinf(char *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	char		*r;

	if (!s1 || !s2)
		return (NULL);
	r = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!r)
		return (NULL);
	j = aconts1(r, s1);
	i = 0;
	while (s2[i] != '\0')
	{
		r[j] = s2[i];
		i++;
		j++;
	}
	free(s1);
	r[j] = '\0';
	return (r);
}