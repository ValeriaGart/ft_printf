/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:42:12 by vharkush          #+#    #+#             */
/*   Updated: 2023/02/09 10:26:06 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

t_yolist	*ft_new(int content, unsigned long long unum,
			char *s, unsigned int u)
{
	t_yolist	*node;

	node = NULL;
	node = malloc(sizeof(t_yolist));
	if (!node)
		return (NULL);
	node->num = content;
	node->unum = unum;
	node->str = s;
	node->u = u;
	node->next = NULL;
	return (node);
}

void	ft_clear(t_yolist **lst)
{
	t_yolist	*tmp;
	t_yolist	*current;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		tmp = current->next;
		if (current)
			free(current);
		current = 0;
		current = tmp;
	}
	*lst = NULL;
}

t_yolist	*ft_list(char *str, int i, va_list args, int num)
{
	t_yolist			*input;
	unsigned long long	unum;
	unsigned int		u;
	char				*s;

	input = NULL;
	s = NULL;
	unum = 0;
	u = 0;
	i++;
	if (bonus_check(str + i))
	{
		while (!ft_strchr("csupxXid%", str[i]))
			i++;
		if (ft_strchr("idc", str[i]))
			num = va_arg(args, int);
		if (ft_strchr("p", str[i]))
			unum = va_arg(args, unsigned long long);
		if (ft_strchr("s", str[i]))
			s = va_arg(args, char *);
		if (ft_strchr("uxX", str[i]))
			u = va_arg(args, unsigned int);
	}
	input = ft_new(num, unum, s, u);
	return (input);
}
