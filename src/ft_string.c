/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:28:06 by vharkush          #+#    #+#             */
/*   Updated: 2023/01/22 16:28:15 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

int	ft_condition_str(int *b, char to_fill, char *to_print, int min)
{
	int	ret;
	int	i;

	ret = 0;
	i = -1;
	if (to_fill != 'u')
	{
		while (*b > 0)
		{
			*b -= 1;
			ret += write(1, &to_fill, 1);
		}
	}
	else
		while (to_print[++i] && --min)
			ret += write(1, &to_print[i], 1);
	return (ret);
}

int	str_bon_len(char *bon, char *str, int inputlen, char *to_print)
{
	int		i;
	char	*str1;

	i = 0;
	if (str)
	{
		str1 = str;
		while (*str1++)
			i++;
		if (ft_strchr(bon, '.'))
		{
			if (to_print == NULL && (ft_numnum(bon, '>') < inputlen))
				i = ft_numnum(bon, '<');
			else if (to_print != NULL && (ft_numnum(bon, '>') < inputlen))
				i = ft_numnum(bon, '<') - ft_numnum(bon, '>');
			else
				i = ft_numnum(bon, '<') - inputlen;
		}
		else
			i -= inputlen;
		return (i);
	}
	else
		return (0);
}

int	saving_lines(char *bon, int inputlen, char *to_print, int i)
{
	int	ret;

	ret = 0;
	if (ft_strchr(bon, '.'))
	{
		if (ft_numnum(bon, '>') < inputlen)
			inputlen = ft_numnum(bon, '>') + 1;
		else
			inputlen = -1;
	}
	else
		inputlen = -1;
	ret += ft_condition_str(&i, 'u', to_print, inputlen);
	return (ret + ft_condition_str(&i, ' ', to_print, 0));
}

int	ft_long_condition(char *bon, int inputlen, char *to_print)
{
	if (to_print == NULL && (ft_numnum(bon, '>') < inputlen)
		&& ft_strchr(bon, '.'))
		return (1);
	else
		return (0);
}

int	ft_print_str(char *to_print, char *str, int ret, char *bon)
{
	int	i;
	int	inputlen;

	inputlen = ret;
	i = str_bon_len(bon, str, inputlen, to_print);
	ret = 0;
	if (!ft_strchr(bon, '-') || ft_long_condition(bon, inputlen, to_print))
	{
		ret += ft_condition_str(&i, ' ', to_print, 0);
		if (ft_strchr(bon, '.'))
		{
			if (to_print != NULL && (ft_numnum(bon, '>') < inputlen))
				i = ft_numnum(bon, '>') + 1;
			else if (to_print == NULL && (ft_numnum(bon, '>') < inputlen))
				i = 1;
		}
		if (to_print != NULL)
			return (ret + ft_condition_str(&i, 'u', to_print, i));
		else
			return (ret + ft_condition_str(&i, 'u', "(null)", i));
	}
	if (to_print != NULL)
		return (saving_lines(bon, inputlen, to_print, i));
	else
		return (saving_lines(bon, inputlen, "(null)", i));
}
