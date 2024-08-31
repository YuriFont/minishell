/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:24:15 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/26 20:05:06 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_nbr(int nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
		i++;
	while (nb != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

static void	ft_putnbr(int fd, int nb)
{
	if (nb == -2147483648)
	{
		ft_printchar(fd, '-');
		ft_printchar(fd, '2');
		ft_putnbr(fd, 147483648);
	}
	else if (nb < 0)
	{
		ft_printchar(fd, '-');
		ft_putnbr(fd, -nb);
	}
	else if (nb > 9)
	{
		ft_putnbr(fd, nb / 10);
		ft_printchar(fd, (nb % 10) + 48);
	}
	else
		ft_printchar(fd, nb + 48);
}

int	ft_printnbr(int fd, int nb)
{
	int		len_print;

	if (nb == 0)
	{
		len_print = ft_printchar(fd, 48);
		return (len_print);
	}
	ft_putnbr(fd, nb);
	len_print = ft_count_nbr(nb);
	return (len_print);
}
