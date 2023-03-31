/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:38:19 by vharkush          #+#    #+#             */
/*   Updated: 2023/01/31 14:26:21 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/ft_printf.h"

int	bonus_new_index(int *incr_ret, int i, char *str, t_yolist *args)
{
	int		s;
	char	*string;

	s = i;
	s++;
	while (!ft_strchr("idusxXpc%", str[s]))
		s++;
	if (str[s] == 's' && bonus_check(str + (i + 1)))
	{
		if (args->str)
		{
			*incr_ret = -2;
			return (s + 1);
		}
		string = args->str;
		if (!string)
		{
			*incr_ret = -2;
			return (s + 1);
		}
	}
	if (*incr_ret == 0)
		return (i++);
	return (s);
}

int	count_args(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '%')
		{
			if (bonus_check(str))
			{
				str++;
				while (ft_strchr("# .+-0123456789", *str))
					str++;
				i++;
			}
		}
		if (str)
			str++;
	}
	return (i);
}

int	ft_no_perc(int incr_ret, char *str, int *num)
{
	int	i;
	int	ret;

	i = *num;
	ret = 0;
	if (incr_ret == -2)
		return (0);
	if (incr_ret == 0 && str[i])
		ret += write(1, &str[i], 1);
	if (str[i])
		i++;
	*num = i;
	return (ret);
}

int	ft_do(char *str1, int *i, va_list args, int *ret)
{
	int			incr_ret;
	t_yolist	*input;

	incr_ret = 0;
	input = ft_list(str1, *i, args, 0);
	incr_ret = bonus_str(str1, *i, input);
	if (incr_ret == -1)
		return (0);
	if (incr_ret != -3)
		*ret += incr_ret;
	*i = bonus_new_index(&incr_ret, *i, str1, input);
	if (input)
		ft_clear(&input);
	return (incr_ret);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		ret;
	int		incr_ret;
	char	*str1;
	va_list	args;

	ret = 0;
	i = 0;
	str1 = (char *)str;
	va_start(args, str);
	while (str1[i])
	{
		incr_ret = 0;
		if (str1[i] == '%')
			incr_ret = ft_do(str1, &i, args, &ret);
		ret += ft_no_perc(incr_ret, str1, &i);
	}
	va_end(args);
	return (ret);
}
