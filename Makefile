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
RLDIR    = $(shell brew --prefix readline)

INCLUDES = -Isrc -I$(RLDIR)/include
CFLAGS   = -Wall -Wextra -Werror $(INCLUDES)
LIBS     = -lreadline -L$(RLDIR)/lib
SRCS	=	src/main.c\
			src/tokenize/tokenize.c\
			src/tokenize/tokenize_utils.c\
			src/tokenize/tokenize_tokens.c\
			src/tokenize/tokenize_skips.c\
			src/parse/parser.c \
			src/parse/parse_new.c \
			src/parse/parse_append.c \
			src/parse/parse_utils.c \
			src/parse/parse_redirect.c \
			src/builtin/builtin.c \
			src/builtin/builtin_cd.c \
			src/builtin/builtin_echo.c \
			src/builtin/builtin_export.c \
			src/builtin/builtin_exit.c \
			src/expand/expand.c \
			src/expand/expand_utils.c \
			src/redirect/redirect.c \
			src/exec/exec.c \
			src/exec/exec_utils.c \
			src/exec/exec_child.c \
			src/exec/exec_builtin.c \
			src/environ/environ.c \
			src/error/error.c\
			src/error/error_utils.c \
			src/free.c\
			src/signal.c\
			src/libft.c


OBJS_DIR = obj
SRCS_DIR = src

SRC    := $(SRCS)
OBJ    := $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))


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

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c src/minishell.h
	mkdir -p $(dir $@)
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
