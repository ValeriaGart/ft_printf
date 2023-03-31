LIBFT = ./libft/libft.a

N_TEMP = temp.a

NAME = libftprintf.a

SRCS = ft_printf.c		\
	src/ft_char.c		\
	src/ft_check_send.c	\
	src/ft_dot_cond.c	\
	src/ft_hexa.c		\
	src/ft_int.c		\
	src/ft_string.c		\
	src/ft_unsint.c		\
	src/utils.c		\
	src/utils2.c		\
	src/ft_list.c

SRC_O = ft_char.o		\
	ft_check_send.o		\
	ft_dot_cond.o		\
	ft_hexa.o		\
	ft_int.o		\
	ft_string.o		\
	ft_unsint.o		\
	utils.o			\
	utils2.o		\
	ft_list.o

CC = cc

CFLAGS = -c -Wextra -Werror -Wall

INCL = -I ./incl

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(MAKE) bonus -C ./libft
	$(MAKE) -C ./libft
	cp libft/libft.a $(NAME)
	ar -rcs $(NAME) $(OBJS)

bonus: $(OBJS)
	$(MAKE) bonus -C ./libft
	$(MAKE) -C ./libft
	cp libft/libft.a $(NAME)
	ar -rcs $(NAME) $(OBJS)

all:	$(NAME)

clean:
	$(MAKE) clean -C ./libft
	rm -rf $(SRC_O)
	rm -rf $(OBJS)

fclean:	clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)

re: fclean all
