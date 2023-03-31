/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:25:45 by vharkush          #+#    #+#             */
/*   Updated: 2023/02/09 10:24:52 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

void	ft_uputnum(unsigned long int n, unsigned long int *i, char *c)
{
	if (n <= 9)
	{
		c[(*i)++] = n + '0';
	}
	else
	{
		ft_putnum(n / 10, (int *)i, c);
		ft_putnum(n % 10, (int *)i, c);
	}
}

char	*ft_uitoa(unsigned int n)
{
	unsigned long int		i;
	unsigned int			num;
	char					*c;

	i = 0;
	num = n;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	c = malloc(sizeof(char) * (i + 1));
	if (c == NULL)
		return (NULL);
	i = 0;
	ft_uputnum(num, &i, c);
	c[i - 1] = '\0';
	return (c);
}

char	*ft_callocproplus(size_t to_alloc, char to_fill)
{
	char	*ret;
	size_t	i;

	i = -1;
	ret = malloc(to_alloc + 1);
	if (!ret)
		return (NULL);
	while (++i < to_alloc)
		ret[i] = to_fill;
	ret[to_alloc] = '\0';
	return (ret);
}

int	ft_bon_len(char *str, int ret, char format, char *bon)
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
		if (format == 'p' || (ft_strchr(bon, '#') && ft_strchr("xX", format)))
			i -= 2;
	}
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
