/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:22:38 by vharkush          #+#    #+#             */
/*   Updated: 2023/02/09 10:23:22 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct hey_list
{
	int					num;
	char				*str;
	unsigned long		unum;
	unsigned int		u;
	struct hey_list		*next;
}			t_yolist;

char		*ft_unitoa(unsigned long int n);
char		*ft_uitoa(unsigned int n);
char		*ft_callocproplus(size_t to_alloc, char to_fill);
char		*ft_dot(char *bon, char format, t_yolist *input);
char		*ft_no_dot(char *bon, char format, t_yolist *input);
char		*ft_change_bon(int dotsign, char *str, int zeros, int spaces);
size_t		ft_strlen(const char *str);
ssize_t		ft_inputlen(char format, t_yolist *input);
int			ft_printf(const char *str, ...);
int			ft_print_hex(unsigned long long num, char format,
				char *str, char *bon);
int			ft_numnum(char *bon, char sign);
int			ft_bon_len(char *str, int ret, char format, char *bon);
int			ft_print_str(char *to_print, char *str, int ret, char *bon);
int			ft_print_unsint(unsigned int input, char *str, int ret, char *bon);
int			ft_print_int(char *bon, int input, char *str, int ret);
int			bonus_for_char(char *bon, char *str, char input, int ret);
int			ft_bonus_send(char *bon, char format, t_yolist *args);
int			bonus_check(char *str);
int			bonus_str(char *str, int i, t_yolist *args);
int			ft_print_x(unsigned int num, char format, char *str, char *bon);
t_yolist	*ft_list(char *str, int i, va_list args, int num);
void		ft_putchar(char c);
void		ft_uputnum(unsigned long int n, unsigned long int *i, char *c);
void		ft_again_recursive(unsigned long long num, char format);
void		ft_clear(t_yolist **lst);
void		ft_putnbr(int nb);

#endif
