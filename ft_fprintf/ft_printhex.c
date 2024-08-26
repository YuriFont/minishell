/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:23:26 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/26 20:04:11 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_counthex(unsigned int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

static void	ft_puthex(int fd, unsigned int n, const char c)
{
	if (n >= 16)
	{
		ft_puthex(fd, n / 16, c);
		ft_puthex(fd, n % 16, c);
	}
	else
	{
		if (n <= 9)
			ft_printchar(fd, n + 48);
		else
		{
			if (c == 'x')
				ft_printchar(fd, n - 10 + 'a');
			if (c == 'X')
				ft_printchar(fd, n - 10 + 'A');
		}
	}
}

int	ft_printhex(int fd, unsigned int n, const char c)
{
	int	len_print;

	len_print = 0;
	if (n == 0)
	{
		len_print += ft_printchar(fd, 48);
		return (len_print);
	}
	len_print += ft_counthex(n);
	ft_puthex(fd, n, c);
	return (len_print);
}
