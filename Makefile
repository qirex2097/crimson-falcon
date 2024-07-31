# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/24 20:04:34 by kahori            #+#    #+#              #
#    Updated: 2024/07/31 09:30:00 by kahori           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############
# Variables #
#############

NAME     = minishell

CC       = cc
RM		= rm -rf

INCLUDES = -I include
CFLAGS   = -Wall -Wextra -Werror $(INCLUDES)
LIBS     = -lreadline
SRCS     = src/main.c\
			src/free.c\
			src/tokenize.c\
			src/error.c\
			src/libft.c

OBJS_DIR = obj
SRCS_DIR = src

SRC    := $(SRCS)
OBJ    := $(SRC:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)


#################
#Color Variable #
#################

CYAN = \033[0;36m
MAGENDA = \033[0;35m
RED = \033[0;31m
LIME = \033[0;32m
RESET = \033[0m

#################
# General rules #
#################

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o  $@ $(LIBS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)


re: fclean all

test: all
	./test.sh
.PHONY: all clean fclean re test

##########################
# Platform Compatibility #
##########################

# Linux | Darwin
OS := $(shell uname -s)

ifeq ($(OS),Linux)
	# commands for Linux
endif

ifeq ($(OS),Darwin)
	# commands for macos
	RLDIR = $(shell brew --prefix readline)
	INCLUDES += -I$(RLDIR)/include
	LIBS     += -L$(RLDIR)/lib
endif