/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:05:51 by vharkush          #+#    #+#             */
/*   Updated: 2023/01/22 19:06:05 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

char	*ft_space_zero(char *bon, int input, char *str, int inputlen)
{
	int	bonlen;
	int	spaces;
	int	zeros;
	int	i;

	spaces = 0;
	zeros = 0;
	i = 0;
	if (!*str || input >= 0)
		return (str);
	bonlen = ft_strlen(str) - inputlen;
	bonlen++;
	while (--bonlen && str[i++] == ' ')
		spaces++;
	i--;
	while (bonlen-- && str[i++] == '0')
		zeros++;
	if (ft_strchr(bon, '.') && !ft_strchr(bon, '-'))
		return (ft_change_bon(1, str, zeros, spaces));
	if (ft_strchr(bon, '.') && ft_strchr(bon, '-'))
		return (ft_change_bon(2, str, zeros, spaces));
	if (!ft_strchr(bon, '-'))
		return (ft_change_bon(3, str, zeros, spaces));
	return (ft_change_bon(4, str, zeros, spaces));
}

int	ft_dot_no_min(int ind, int input, char *str, int bonlen)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	if ((bonlen <= 0 || str[i] != ' ') && input < 0 && !ind)
		ret += write(1, "-", 1);
	if (input < 0)
	{
		ret--;
		input *= -1;
		if (ind)
			write(1, "-", 1);
	}
	if (ind)
		return (input);
	while (bonlen-- && bonlen >= 0 && *str)
		ret += write(1, &str[i++], 1);
	if (input != 0)
		ft_putnbr(input);
	else
		ret--;
	return (ret);
}

int	ft_dot_int(int input, char *str, int bonlen)
{
	int	ret;
	int	i;
	int	temp;

	ret = 0;
	i = 0;
	temp = bonlen;
	input = ft_dot_no_min(1, input, str, bonlen);
	while ((str[i] == ' ' || str[i] == '-') && bonlen > 0 && bonlen--)
		i++;
	if (str[i] && input != 0)
		i++;
	while (str[i++] == '0' && bonlen > 0 && bonlen--)
		ret += write(1, "0", 1);
	if (input != 0)
		ft_putnbr(input);
	else
		ret--;
	i = 0;
	while (*str && str[i++] != '0' && temp > 0 && temp--)
	{
		if (str[i - 1] != '-')
			ret += write(1, " ", 1);
	}
	return (ret);
}

int	ft_no_dot_int(char *bon, int input, char *str, int bonlen)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	if (ft_strchr(bon, '-'))
	{
		ft_putnbr(input);
		if (input <= 0)
			bonlen--;
		while (bonlen > 0 && bonlen--)
			ret += write(1, " ", 1);
		return (ret);
	}
	if (input < 0 && *str && *str != '0' && bonlen > 0)
	{
		ret--;
		input *= -1;
	}
	if (input == 0)
		bonlen--;
	while (bonlen > 0 && bonlen--)
		ret += write(1, &str[i++], 1);
	ft_putnbr(input);
	return (ret);
}

int	ft_print_int(char *bon, int input, char *str, int ret)
{
	int	bonlen;

	if (input <= 0)
		ret--;
	str = ft_space_zero(bon, input, str, ret);
	bonlen = ft_strlen(str) - ret;
	ret = 0;
	if (ft_strchr(bon, '.'))
	{
		if (ft_strchr(bon, '+') && input > 0)
			ret += write(1, "+", 1);
		if (ft_strchr(bon, '-'))
			ret += ft_dot_int(input, str, bonlen);
		else
			ret += ft_dot_no_min(0, input, str, bonlen);
		return (ret);
	}
	if (input == -2147483648 && bonlen <= 0)
		write(1, "-", 1);
	ret += ft_no_dot_int(bon, input, str, bonlen);
	return (ret);
}
