/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:29:26 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/20 15:08:06 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_size(long long n)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	if (n < 0)
		sign = 1;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i + sign);
}

long long	ft_abs(long long n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

char	*ft_ltoa(long long n)
{
	char			*r;
	int				i;
	long long		assist;

	assist = n;
	i = count_size(n);
	r = malloc(sizeof(char) * (i + 1));
	if (!r)
		return (NULL);
	i--;
	while (i >= 0)
	{
		if (i == 0 && n < 0)
			r[i] = '-';
		else
		{
			r[i] = ft_abs(assist % 10) + 48;
			assist = assist / 10;
		}
		i--;
	}
	r[count_size(n)] = '\0';
	return (r);
}
