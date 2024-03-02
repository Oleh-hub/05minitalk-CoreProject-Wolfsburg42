# https://medium.com/@oduwoledare/42-minitalk-explained-5b236adc2c24

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g

NAME_SRVR	:= server
SRVR_SRCS	:= server.c
SRVR_OBJS	:= $(SRVR_SRCS:.c=.o)

NAME_CLNT	:= client
CLNT_SRCS	:= client.c
CLNT_OBJS	:= $(CLNT_SRCS:.c=.o)

NAME_SRVR_BONUS	:= server_bonus
SRVR_BONUS_SRCS	:= server_bonus.c
SRVR_BONUS_OBJS	:= $(SRVR_BONUS_SRCS:.c=.o)

NAME_CLNT_BONUS	:= client_bonus
CLNT_BONUS_SRCS	:= client_bonus.c
CLNT_BONUS_OBJS	:= $(CLNT_BONUS_SRCS:.c=.o)

LIBPATH	:= ./libft/
LIB		:= $(LIBPATH)libft.a

all: $(NAME_SRVR) $(NAME_CLNT)

$(NAME_SRVR): $(SRVR_OBJS) $(LIB)
	$(CC) $(CFLAGS) $(SRVR_OBJS) $(LIB) -o $@ 

$(NAME_CLNT): $(CLNT_OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $(CLNT_OBJS) -L$(LIBPATH) -lft

$(NAME_SRVR_BONUS): $(SRVR_BONUS_OBJS) $(LIB)
	$(CC) $(CFLAGS) $(SRVR_BONUS_OBJS) $(LIB) -o $@ 

$(NAME_CLNT_BONUS): $(CLNT_BONUS_OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $(CLNT_BONUS_OBJS) -L$(LIBPATH) -lft

$(LIB):
	make -C $(LIBPATH) all bonus

clean:
	rm -f $(SRVR_OBJS) $(CLNT_OBJS) $(SRVR_BONUS_OBJS) $(CLNT_BONUS_OBJS)
	make -C $(LIBPATH) clean fclean

fclean: clean
	rm -f $(NAME_SRVR) $(NAME_CLNT) $(NAME_SRVR_BONUS) $(NAME_CLNT_BONUS)
	make -C $(LIBPATH) $@

bonus:  $(NAME_SRVR_BONUS) $(NAME_CLNT_BONUS)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
