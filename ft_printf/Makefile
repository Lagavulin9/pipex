CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_printf.c utils.c utils2.c utils3.c utils4.c utils5.c
BONUS_SRCS = $(SRCS:.c=_bonus.c)
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
INC = ft_printf.h
BONUS_INC = ft_printf_bonus.h
NAME = libftprintf.a

ifdef BONUSFLAG
	OBJECT = $(BONUS_OBJS)
	INCLUDE = $(BONUS_INC)
else 
	OBJECT = $(OBJS)
	INCLUDE = $(INC)
endif

all : $(NAME)

$(NAME) : $(OBJECT)
	ar rcs $(NAME) $(OBJECT)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ -I $(INCLUDE) $<

#$(OBJS) : $(SRCS)
#	$(CC) $(CFLAGS) -c -o $@ -I $(INC) $<

#$(BONUS_OBJS) : $(BONUS_SRCS)
#	$(CC) $(CFLAGS) -c -o $@ -I $(INC) $<

clean : 
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

bonus :
	make BONUSFLAG=1 all

.PHONY : all clean fclean re all