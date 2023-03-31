/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_cond.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:39:36 by vharkush          #+#    #+#             */
/*   Updated: 2023/01/22 19:39:52 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

char	*alloc_no_dot(int i, char *bon)
{
	char	*str;
	char	*str1;

	str1 = bon;
	if (str1 && i > 0)
	{
		if (*str1 == '0')
			str = ft_callocproplus(i, '0');
		else
			str = ft_callocproplus(i, ' ');
	}
	else
		str = ft_callocproplus(1, '\0');
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_no_dot(char *bon, char format, t_yolist *input)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if (bon)
		i = ft_numnum(bon, '<');
	if ((format == 'd' || format == 'i')
		&& (ft_strchr(bon, '+') || ft_strchr(bon, ' ')))
	{
		if (ft_strchr(bon, '+') && input->num >= 0)
			write(1, "+", 1);
		else if (ft_strchr(bon, ' ') && input->num >= 0)
			write(1, " ", 1);
		if (input->num > 0)
			i--;
	}
	str = alloc_no_dot(i, bon);
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_alloc_pls(char *bon, char format, int i)
{
	int		b;
	char	*str;

	b = 0;
	if (bon)
	{
		i = ft_numnum(bon, '<');
		b = ft_numnum(bon, '>');
	}
	if (b >= i && format != 'c')
		str = ft_callocproplus(b, '0');
	else if (i > b || format == 'c')
	{
		str = ft_callocproplus(i, ' ');
		while (b-- && format != 'c' && i != 0)
			str[--i] = '0';
	}
	else
		str = ft_callocproplus(2, '\0');
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_dot(char *bon, char format, t_yolist *input)
{
	char	*str;

	str = ft_alloc_pls(bon, format, 0);
	if (!str)
		return (NULL);
	if (format == 'd' || format == 'i')
	{
		if (ft_strchr(bon, '+') && input->num >= 0)
			write(1, "+", 1);
		else if (ft_strchr(bon, ' ') && input->num >= 0)
			write(1, " ", 1);
	}
	return (str);
}
