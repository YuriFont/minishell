/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:38:38 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/26 20:05:48 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_ptr(unsigned long long ptr)
{
	int	i;

	i = 0;
	while (ptr != 0)
	{
		ptr = ptr / 16;
		i++;
	}
	return (i);
}

static void	ft_putptr(int fd, unsigned long long ptr)
{
	if (ptr >= 16)
	{
		ft_putptr(fd, ptr / 16);
		ft_putptr(fd, ptr % 16);
	}
	else
	{
		if (ptr <= 9)
			ft_printchar(fd, ptr + 48);
		else
			ft_printchar(fd, (ptr - 10) + 'a');
	}
}

int	ft_printptr(int fd, unsigned long long ptr)
{
	int	len_print;

	if (ptr == 0)
	{
		len_print = ft_printstr(fd, "(nil)");
		return (len_print);
	}
	len_print = 0;
	len_print += write(fd, "0x", 2);
	ft_putptr(fd, ptr);
	len_print += ft_count_ptr(ptr);
	return (len_print);
}
