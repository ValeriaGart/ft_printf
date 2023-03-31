/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:26:25 by vharkush          #+#    #+#             */
/*   Updated: 2023/01/22 12:26:33 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

int	ft_condition(int b, char to_fill, int format, unsigned long long num)
{
	int	ret;

	ret = 0;
	if (to_fill != 'u' && to_fill != 'a')
		while (b > 0 && b--)
			ret += write(1, &to_fill, 1);
	if (to_fill == 'u')
		ft_again_recursive(num, format);
	if (to_fill == 'a')
	{
		if (num == 0)
			return (1);
		while (num > 0 && to_fill == 'a')
		{
			ret++;
			num = num / 16;
		}
	}
	return (ret);
}

int	ft_dot_condition(char *bon, char format, unsigned long long num, int i)
{
	int	ret;
	int	inputlen;
	int	b;

	b = ft_numnum(bon, '<');
	inputlen = ft_condition(0, 'a', format, num);
	i = i - inputlen;
	inputlen += i;
	b -= inputlen;
	if (format == 'p' || ft_strchr(bon, '#'))
		b -= 2;
	ret = 0;
	if (!ft_strchr(bon, '-'))
		ret += ft_condition(b, ' ', format, num);
	if (format == 'p' || (format == 'x' && ft_strchr(bon, '#')))
		ret += write(1, "0x", 2);
	if (format == 'X' && ft_strchr(bon, '#'))
		ret += write(1, "0X", 2);
	ft_condition(i, '0', format, num);
	ft_condition(0, 'u', format, num);
	if (ft_strchr(bon, '-'))
		ret += ft_condition(b, ' ', format, num);
	return (ret + inputlen);
}

int	check_special(char *bon, unsigned long long num, char format, int ind)
{
	int	ret;

	ret = 0;
	if (ind)
	{
		if (format == 'p' && ft_strchr(bon, '+'))
			ret += write(1, "+", 1);
		else if (format == 'p' && ft_strchr(bon, ' '))
			ret += write(1, " ", 1);
		return (ret);
	}
	if (format == 'p' || (format == 'x' && ft_strchr(bon, '#') && num != 0))
		ret += write(1, "0x", 2);
	if (format == 'X' && ft_strchr(bon, '#') && num != 0)
		ret += write(1, "0X", 2);
	if (!(num == 0 && ft_strchr(bon, '.') && !ft_numnum(bon, '>')))
		ft_condition(0, 'u', format, num);
	return (ret);
}

int	ft_default_cond(char *bon, char format, unsigned long long num, char *str)
{
	int	ret;
	int	i;

	ret = ft_condition(0, 'a', format, num);
	i = ft_bon_len(str, ret, format, bon);
	ret = 0;
	if (num == 0 && !ft_numnum(bon, '>') && ft_strchr(bon, '.'))
	{
		if (ft_numnum(bon, '<'))
			i++;
		while (i-- && i >= 0)
			ret += write(1, " ", 1);
		return (ret);
	}
	ret += check_special(bon, num, format, 1);
	if (format == 'p' && (ft_strchr(bon, ' ') || ft_strchr(bon, '+')) && i > 0)
		i--;
	if (!ft_strchr(bon, '-'))
		while (i-- && i >= 0)
			ret += write(1, &str[ret], 1);
	ret += check_special(bon, num, format, 0);
	while (i-- && i >= 0 && ft_strchr(bon, '-'))
		ret += write(1, " ", 1);
	ret += ft_condition(0, 'a', format, num);
	return (ret);
}

int	ft_print_hex(unsigned long long num, char format, char *str, char *bon)
{
	int		i;
	int		ret;

	if (num == 0 && format == 'p' && ft_strchr(bon, '.'))
		return (write(1, "(nil)", 5));
	else if (num == 0 && format == 'p' && !ft_strchr(bon, '.'))
		return (ft_print_str("(nil)", str, 5, bon));
	ret = ft_condition(0, 'a', format, num);
	if (ft_strchr(bon, '.'))
	{
		i = ft_numnum(bon, '>');
		if (i > ret)
			return (ft_dot_condition(bon, format, num, i));
	}
	return (ft_default_cond(bon, format, num, str));
}
