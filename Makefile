# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/07 12:54:34 by ladawi            #+#    #+#              #
#    Updated: 2022/03/23 19:43:38 by ladawi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = clang
HEAD = -Iincludes
CFLAGS = -Wall -Wextra $(DEBUG) -pthread -g3
# DEBUG = -fsanitize=thread


FILES = main.c \
		setup_philo.c \
		set_settings.c \
		utils.c \
		utils2.c \
		utils3.c \
		singleton.c \
		ft_usleep.c \
		thread.c \
		routine.c \
		check_overflow.c \
		philo_eat.c

SRC_PATH = $(shell find srcs -type d)
vpath %.c $(foreach dir, $(SRC_PATH), $(dir))

OBJ_PATH = objs
OBJ = $(addprefix $(OBJ_PATH)/, $(FILES:%.c=%.o))

END = \033[0m
RED = \033[0;91m
YEL = \033[93m
GRE = \033[0;92m
PUR = \033[0;95m
BLU = \033[0;34m
BOLD = \033[1m


all :   $(NAME)

$(NAME) : $(OBJ_PATH) $(OBJ) ./includes/philo.h
	@echo "$(YEL)Made $(NAME)$(END)"
	@echo "$(PUR)Compiling$(END)"
	@$(CC) $(CFLAGS) $(HEAD) $(OBJ) -o ${NAME}

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o : %.c
	@$(CC) $(CFLAGS) $(HEAD) -c $< -o $@
	@echo "$(GRE)$@$(END)"

print:
	@echo $(OBJ)

clean:
	@rm -rf $(OBJ)
	@echo "$(RED)$(BOLD)Removed *.o $(END)"
	@echo "$(RED)$(BOLD)Made [clean] in libft$(END)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)$(BOLD)Removed $(NAME) $(END)"
	@echo "$(RED)$(BOLD)Made [fclean] in libft$(END)"

re: fclean all