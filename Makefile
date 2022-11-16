NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra
GNL_DIR = get_next_line/
GNL_SRC = get_next_line.c get_next_line_utils.c
PRINTF_DIR = ft_printf/
PRINTF_SRC = ft_printf.c utils.c utils2.c utils3.c utils4.c utils5.c
SRC_DIR = srcs/
SRC = pipex.c ft_malloc.c
SRC_BONUS_DIR = srcs_bonus/
SRC_BONUS = 
SRCS = $(addprefix $(SRC_DIR), $(SRC)) $(addprefix $(PRINTF_DIR), $(PRINTF_SRC))
SRCS_BONUS = $(SRCS) \
			$(addprefix $(GNL_DIR), $(GNL_SRC)) $(addprefix $(SRC_BONUS_DIR), $(SRC_BONUS))
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o) $(GNL_SRC:.c=.o)
INCLUDE = pipex.h
LIBFT = libft/libft.a

ifdef SANITIZE
	CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
endif

ifdef BONUS
	OBJS = $(SRCS_BONUS:.c=.o) $(GNL_SRC:.c=.o)
endif

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ -I libft -I get_next_line -I ft_printf $<

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft all

clean : 
	@$(MAKE) -C ./libft clean
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean : clean
	@$(MAKE) -C ./libft fclean
	rm -rf $(NAME) $(NAME_BONUS)

re : fclean all

bonus :
	make BONUS=1 all

sanitize :
	make SANITIZE=1 re

.PHONY: all clean fclean re libft bonus sanitize