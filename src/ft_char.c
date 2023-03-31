/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:33:47 by vharkush          #+#    #+#             */
/*   Updated: 2023/01/22 19:34:02 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

int	bonus_for_char(char *bon, char *str, char input, int ret)
{
	int		i;
	char	*str1;

	i = 0;
	if (str[0] != '\0')
	{
		str1 = str;
		while (*str1++)
			i++;
		i -= ret;
	}
	ret = 0;
	if (!ft_strchr(bon, '-'))
		while (i--)
			ret += write(1, " ", 1);
	ft_putchar(input);
	if (ft_strchr(bon, '-'))
		while (i--)
			ret += write(1, " ", 1);
	return (ret);
}
