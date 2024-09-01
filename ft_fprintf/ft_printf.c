/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:30:48 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/26 20:04:12 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_formats(int fd, va_list args, const char type)
{
	int	len_print;

	len_print = 0;
	if (type == 'c')
		len_print += ft_printchar(fd, va_arg(args, int));
	else if (type == 's')
		len_print += ft_printstr(fd, va_arg(args, char *));
	else if (type == 'p')
		len_print += ft_printptr(fd, va_arg(args, unsigned long long));
	else if (type == 'd' || type == 'i')
		len_print += ft_printnbr(fd, va_arg(args, int));
	else if (type == 'u')
		len_print += ft_print_unsint(fd, va_arg(args, unsigned int));
	else if (type == 'x' || type == 'X')
		len_print += ft_printhex(fd, va_arg(args, unsigned int), type);
	else if (type == '%')
		len_print += ft_printchar(fd, '%');
	return (len_print);
}

int	ft_fprintf(int fd, const char *s, ...)
{
	int		i;
	int		len_printf;
	va_list	args;

	i = 0;
	len_printf = 0;
	va_start(args, s);
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			len_printf += ft_formats(fd, args, s[i + 1]);
			i++;
		}
		else
			len_printf += ft_printchar(fd, s[i]);
		i++;
	}
	va_end(args);
	return (len_printf);
}
