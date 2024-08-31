/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:55:15 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/26 20:06:20 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printchar(int fd, char c);
int	ft_printstr(int fd, const char *s);
int	ft_printnbr(int fd, int nb);
int	ft_printptr(int fd, unsigned long long ptr);
int	ft_print_unsint(int fd, unsigned int n);
int	ft_printhex(int fd, unsigned int n, const char c);
int	ft_fprintf(int fd, const char *s, ...);

#endif
