# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mounali <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 22:21:17 by mounali           #+#    #+#              #
#    Updated: 2023/10/02 22:30:38 by mounali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = cd_pwd.c echo.c echo2.c env.c export.c main.c\
       executable.c executable2.c find_path.c parse_redirec.c\
       pipe.c prompt.c quote.c redirec.c unset.c utils.c\
       utils2.c utils3.c utils4.c utils5.c pipe2.c pipe3.c\
	   mix_and_twist.c allretour.c heredoc.c creation_pipe.c\
	   redirec_pipe.c pipe2a.c parse_redirec2.c executable3.c\
	   quote2.c
	   

HDRS = minishell.h

OBJS = $(SRCS:.c=.o)

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lreadline -lncurses

RM = rm -f

all: $(NAME)

$(MOBJS):$(HDRS) Makefile
$(OBJS):$(HDRS) Makefile

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):$(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

