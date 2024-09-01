/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:25:03 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/26 20:04:13 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count(unsigned int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	ft_putunsnbr(int fd, unsigned int nb)
{
	if (nb > 9)
	{
		ft_putunsnbr(fd, nb / 10);
		ft_printchar(fd, (nb % 10) + 48);
	}
	else
		ft_printchar(fd, nb + 48);
}

int	ft_print_unsint(int fd, unsigned int n)
{
	int		len_print;

	len_print = 0;
	if (n == 0)
		len_print += ft_printchar(fd, 48);
	else
	{
		ft_putunsnbr(fd, n);
		len_print += ft_count(n);
	}
	return (len_print);
}
