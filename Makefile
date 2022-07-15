# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 16:26:13 by tiemen            #+#    #+#              #
#    Updated: 2022/07/15 09:55:19 by tbouma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
OBJFILES := obj/src/main.o obj/src/utils.o obj/src/path_command.o obj/src/parsing.o
LIBFT := includes/libft/libft.a
HEADERS := -I libft/
CFLAGS := -Wall -Wextra -Werror 
CC := gcc

all: $(LIBFT) $(NAME)

$(LIBFT): 
	make -C ./includes/libft

$(NAME): $(OBJFILES)
	cp $(LIBFT) $(NAME)
	$(CC) $(CFLAGS) $(OBJFILES) $(LIBFT) $(HEADERS) -o $(NAME) -lreadline

obj/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJFILES)
	make clean -C ./includes/libft

fclean:	clean
	rm -f $(NAME)
	make fclean -C ./includes/libft

re: fclean all

.PHONY: clean all fclean re