# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/21 17:21:50 by vsaltel           #+#    #+#              #
#    Updated: 2019/03/13 17:19:27 by vsaltel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
#CFLAGS	+=	-Wall -Werror -Wextra
#CFLAGS = -g -fsanitize=address

NAME 	=	minishell
LIBFT	=	libft
SRCDIR	=	src
INCDIR	=	include
OBJDIR	=	objs
FILES 	=	minishell.c			\
			lexer.c				\
			lexer2.c			\
			parser.c			\
			regex.c				\
			free.c				\
			utils.c				\
			utils2.c			\
			error.c				\
			exec.c				\
			builtin/cd.c		\
			builtin/env.c		\
			builtin/unsetenv.c	\
			builtin/setenv.c	\
			builtin/echo.c		\
			builtin/exit.c		\
			main.c

SRCS	=	$(addprefix $(SRCDIR)/, $(FILES))
OBJS 	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

##### Colors #####
_END=\x1b[0m
_BOLD=\x1b[1m
_UNDER=\x1b[4m
_REV=\x1b[7m
_GREY=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m

.PHONY: all clean fclean re $(LIBFT)

$(NAME): $(OBJS)
	@$(MAKE) -q -C $(LIBFT) || $(MAKE) -C $(LIBFT)
	@echo "${_BLUE}${_BOLD}[Create Executable] $(NAME)${_END}"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./$(LIBFT) -lft
	@echo "${_GREEN}${_BOLD}$(NAME) done.${_END}"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	@[ -d $(OBJDIR)/builtin ] || mkdir -p $(OBJDIR)/builtin
	@echo "${_PURPLE}Compiling $<${_END}"
	@$(CC) $(CFLAGS) -I $(INCDIR) -I $(LIBFT)/include -o $@ -c $<

all: $(NAME)

clean:
	@make -C $(LIBFT) clean
	@echo "${_RED}${_BOLD}Cleaning obj files...${_END}"
	@rm -f $(OBJS)

fclean: clean
	@make -C $(LIBFT) fclean
	@echo "${_RED}${_BOLD}Cleaning project...${_END}"
	@rm -f $(NAME)

re: fclean $(NAME)
