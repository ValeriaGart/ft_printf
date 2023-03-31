/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:55:07 by vharkush          #+#    #+#             */
/*   Updated: 2023/01/22 18:55:22 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

char	*ft_change_bon(int dotsign, char *str, int zeros, int spaces)
{
	if ((dotsign == 1 || dotsign == 2) && *str)
	{
		if (dotsign == 2 && spaces > 0)
			str[0] = '-';
		else if (spaces > 0)
			str[spaces - 1] = '-';
	}
	if ((dotsign == 3 || dotsign == 4) && *str)
	{
		if (dotsign == 4 && zeros > 0)
			str[0] = '-';
		else if (dotsign == 4 && spaces > 0)
			str[0] = '-';
		else if (zeros > 0)
			str[0] = '-';
		else if (spaces > 0)
			str[spaces - 1] = '-';
	}
	return (str);
}

void	ft_uputnbr(unsigned int nb)
{
	unsigned long int	x;

	x = 48;
	if (nb >= 10)
	{
		ft_uputnbr(nb / 10);
		ft_uputnbr(nb % 10);
	}
	else
		ft_putchar(nb + x);
}

int	ft_assign_write(char *bon, int b, int i, int ind)
{
	int	ret;

	ret = 0;
	if (ind)
	{
		if (ft_numnum(bon, '<') > ft_numnum(bon, '>'))
			b = i - (ft_numnum(bon, '<') - ft_numnum(bon, '>'));
		else
			b = i;
		return (b);
	}
	i = i - b;
	b++;
	while (b-- && b > 0)
		ret += write(1, "0", 1);
	return (ret);
}

int	ft_dot_or_no_min(char *bon, int i, char *str, unsigned int input)
{
	int	b;
	int	ret;

	ret = 0;
	b = ft_assign_write(bon, 0, i, 1);
	if (!(ft_strchr(bon, '.') && ft_strchr(bon, '-')))
		while (i-- && i >= 0)
			ret += write(1, &str[ret], 1);
	else if (b > 0)
		ret += ft_assign_write(bon, b, i, 0);
	b = 0;
	if (input != 0 || (input == 0 && !ft_strchr(bon, '.')))
		ft_uputnbr(input);
	else
		ret--;
	if (ft_strchr(bon, '.') && ft_strchr(bon, '-'))
		while (i-- && i >= 0 && str[b] == ' ')
			ret += write(1, &str[b++], 1);
	return (ret);
}

int	ft_print_unsint(unsigned int input, char *str, int ret, char *bon)
{
	int	i;

	i = ft_bon_len(str, ret, 'u', bon);
	if (input == 0 && ft_strchr(bon, '.'))
		i++;
	ret = 0;
	if (ft_strchr(bon, '-') && !ft_strchr(bon, '.'))
	{
		ft_uputnbr(input);
		while (i-- && i >= 0)
			ret += write(1, " ", 1);
	}
	else
		ret = ft_dot_or_no_min(bon, i, str, input);
	return (ret);
}
