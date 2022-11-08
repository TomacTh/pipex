CC		=	gcc
NAME	=	pipex
NAME_BONUS =	pipex_bonus
CFLAGS	= 	-Wall -Wextra -Werror
INC		=	./inc
SRCS	=	$(addprefix ./srcs/, pipex.c \
						fd_utils3.c)
SRCSUTILS= $(addprefix ./utils/, ft_utils1.c ft_utils2.c ft_split.c)
SRCSBONUS=  $(addprefix ./srcsbonus/, pipex_bonus.c init_bonus.c utils_bonus.c utils2_bonus.c get_next_line_bonus.c)

OBJS	=	$(SRCS:.c=.o)
OBJSUTILS =  $(SRCSUTILS:.c=.o)
OBJSBONUS =	$(SRCSBONUS:.c=.o)

all:	$(NAME)

bonus: $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(NAME):	$(OBJS) $(OBJSUTILS)
	$(CC) $(CFLAGS) $(OBJS) $(OBJSUTILS) -o $(NAME)

$(NAME_BONUS):	$(OBJSBONUS) $(OBJSUTILS)
	$(CC) $(CFLAGS) $(OBJSBONUS) $(OBJSUTILS) -o $(NAME_BONUS)

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJSUTILS)
	rm -rf $(OBJSBONUS)

fclean:	clean
	rm -f $(NAME) $(NAME_BONUS)


re:	fclean all

.PHONY:	all bonus clean re install
