/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_send.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 20:34:55 by vharkush          #+#    #+#             */
/*   Updated: 2023/01/22 20:35:14 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

int	ft_ready_go(char format, t_yolist *args, char *bon, char *str)
{
	int	ret;

	ret = ft_inputlen(format, args);
	if (args->num == 0 && args->u == 0 && !ft_numnum(bon, '<')
		&& !ft_numnum(bon, '>') && ft_strchr("iduxX", format)
		&& ft_strchr(bon, '.'))
		return (-3);
	if (format == 'c')
		ret += bonus_for_char(bon, str, args->num, ret);
	if (ft_strchr("id%", format))
		ret += ft_print_int(bon, args->num, str, ret);
	if (format == 'u')
		ret += ft_print_unsint(args->u, str, ret, bon);
	if (ft_strchr("p", format))
		ret = ft_print_hex(args->unum, format, str, bon);
	if (ft_strchr("xX", format))
		ret = ft_print_hex(args->u, format, str, bon);
	if (format == 's')
		ret = ft_print_str(args->str, str, ret, bon);
	return (ret);
}

int	ft_bonus_send(char *bon, char format, t_yolist *args)
{
	int		ret;
	char	*str;

	ret = ft_inputlen(format, args);
	if (ret == -1)
		return (-1);
	if (ft_strchr(bon, '.'))
		str = ft_dot(bon, format, args);
	else
		str = ft_no_dot(bon, format, args);
	if (!str)
		return (-1);
	ret = ft_ready_go(format, args, bon, str);
	if ((ft_strchr(bon, ' ') || ft_strchr(bon, '+')) && ft_strchr("id", format))
	{
		if (args->num >= 0)
			ret++;
	}
	free (str);
	return (ret);
}

int	bonus_check(char *str)
{
	int	i;
	int	ind;

	i = 0;
	ind = 0;
	while (str[i + 1] && ft_strchr("# +-0", str[i]))
		i++;
	while (str[i + 1] && ft_isdigit(str[i]))
		i++;
	if (str[i + 1] && str[i] == '.')
	{
		i++;
		ind++;
	}
	while (str[i + 1] && ft_isdigit(str[i]) && ind == 1)
		i++;
	if (ft_strchr("idusxXpc%", str[i]))
		i = -1;
	if (i == -1)
		return (1);
	return (0);
}

int	bonus_str(char *str, int i, t_yolist *args)
{
	int		ret;
	int		rem_i;
	char	*bon;

	if (!str[i + 1])
		return (0);
	if (!bonus_check(str + (i + 1)))
		return (0);
	rem_i = i + 1;
	ret = 0;
	while (!ft_strchr("idusxXpc%", str[++i]))
		ret++;
	if (str[i] == '%')
		return (write(1, "%", 1));
	bon = ft_substr(str, rem_i, ret);
	if (!bon)
		return (-1);
	ret = ft_bonus_send(bon, str[i], args);
	free (bon);
	return (ret);
}
