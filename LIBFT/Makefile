NAME = libftprintf.a 

CC = cc

CFLAFGS = -Wall -Wextra -Werror

LIB = ./libft/libft.a

M_LIB = ./ft_malloc/ft_malloc.a


INC = -I INCLUDES

SRCS_PATH = SRCS
SRCS_NAME = \
	ft_printf.c \
	ft_putstr.c \
	ft_putchar.c \
	ft_pformat.c \
	ft_putnbr.c \
	ft_putunsigned.c \
	ft_put_hexa.c \
	ft_putsign.c \
	ft_putptr.c \
	get_next_line.c \
	get_next_line_utils.c 
SRCS = $(addprefix $(SRCS_PATH)/,$(SRCS_NAME))

OBJS_PATH = OBJS
OBJS_NAME = $(SRCS_NAME:.c=.o)
OBJS = $(addprefix $(OBJS_PATH)/,$(OBJS_NAME))

all : $(NAME)

libftcomp :
	@make -C ./ft_malloc
	@make all -C ./libft

$(NAME) : libftcomp $(OBJS) $(LIB) $(M_LIB)
	@libtool -static -o $@ $(LIB) $(M_LIB) $(OBJS)

$(OBJS) : $(OBJS_PATH) $(SRCS)
	@$(CC) $(CFLAFGS) $(INC) -c $(SRCS)
	@mv $(OBJS_NAME) $(OBJS_PATH) 

$(OBJS_PATH) :
	@mkdir OBJS 2> /dev/null || true

clean :
	@make clean -C ./libft
	@make clean -C ./ft_malloc
	@rm -f $(OBJS)
	@rmdir -p $(OBJS_PATH) 2> /dev/null || true

fclean : clean
	@make fclean -C ./libft
	@make fclean -C ./ft_malloc
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
