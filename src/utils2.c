/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:59:52 by vharkush          #+#    #+#             */
/*   Updated: 2023/02/06 19:00:03 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

void	ft_putnbr(int nb)
{
	int	x;

	x = 48;
	if (nb == -2147483648)
	{
		write(1, "2", 1);
		nb = 147483648;
	}
	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
	{
		ft_putchar(nb + x);
	}
}

void	ft_again_recursive(unsigned long long num, char format)
{	
	if (num <= 9)
		ft_putchar(num + '0');
	else if (num < 16)
	{
		if (format == 'X')
			ft_putchar(num + 'A' - 10);
		else
			ft_putchar(num + 'a' - 10);
	}
	else if (num >= 16)
	{
		ft_again_recursive(num / 16, format);
		ft_again_recursive(num % 16, format);
	}
}

char	*ft_unitoa(unsigned long int n)
{
	char				*c;
	unsigned long int	i;
	unsigned long int	num;

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

ssize_t	ft_inputlen(char format, t_yolist *input)
{
	long int	inputlen;
	char		*str;

	if (ft_strchr("siduxX", format) && !(format == 's' && input->str == NULL))
	{
		if (format == 's')
			str = ft_strdup(input->str);
		else if (ft_strchr("idc", format))
			str = ft_itoa(input->num);
		else if (format != 'p')
			str = ft_uitoa(input->u);
		else
			str = ft_unitoa(input->unum);
		if (!str)
			return (-1);
		inputlen = ft_strlen(str);
		if (format == 'u')
			inputlen++;
		free (str);
	}
	else if (format == 's' && input->str == NULL)
		inputlen = 6;
	else
		inputlen = 1;
	return (inputlen);
}

int	ft_numnum(char *bon, char sign)
{
	int	i;

	i = 0;
	if (!bon)
		return (0);
	if (sign == '<')
	{
		while (!ft_strchr("123456789",*bon) && bon && *bon != '.')
			bon++;
		if (!bon || *bon == '.')
			return (0);
		while (bon && *bon != '.' && *bon != '\0')
		{
			i = (i * 10) + (*bon - 48);
			bon++;
		}
		return (i);
	}
	while (bon && *bon != '.' && *bon != '\0')
		bon++;
	if (bon && (*bon != '\0'))
		bon++;
	while (bon && *bon)
		i = (i * 10) + (*(bon++) - 48);
	return (i);
}
