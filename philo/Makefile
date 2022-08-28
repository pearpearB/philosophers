# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/24 15:25:57 by jabae             #+#    #+#              #
#    Updated: 2022/08/28 19:59:50 by jabae            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	philo.c \
		init.c \
		run.c \
		utils.c \

OBJS = $(SRCS:%.c=%.o)

FLAGS	= -Wall -Wextra -Werror -fsanitize=thread -g3

all	: $(NAME)

$(NAME)	:	$(OBJS)
		@cc $(FLAGS)  -o $(NAME) $(OBJS)
		@echo "🍽 MAKE SUCCESS"

%.o	:	%.c
	@cc $(FLAGS) -c $^ -I./

clean	: 
		@rm -f $(OBJS)
		@echo "🍽 CLEAN SUCCESS"

fclean	: 	clean
		@rm -f $(NAME)
		@echo "🍽 FCLEAN SUCCESS"

re : fclean all

.PHONY	: all clean fclean re