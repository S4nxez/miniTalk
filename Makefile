# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dansanc3 <dansanc3@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/02 18:46:52 by dansanc3          #+#    #+#              #
#    Updated: 2025/08/02 18:56:50 by dansanc3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client

SRC_SERVER = src/server.c src/utils.c
SRC_CLIENT = src/client.c src/utils.c
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

# Ft_printf library path
FT_PRINTF_DIR = include/ft_printf
FT_PRINTF_DIR_INCLUDE = include/ft_printf/include
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

# Libft library path
LIBFT_DIR = include/libft/
LIBFT_DIR_INCLUDE = $(LIBFT_DIR)include
LIBFT = $(LIBFT_DIR)libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include -I $(FT_PRINTF_DIR_INCLUDE) -I $(LIBFT_DIR_INCLUDE) -fsanitize=address -fno-omit-frame-pointer -g

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_SERVER) $(FT_PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(FT_PRINTF) $(LIBFT) -o $@

$(CLIENT): $(OBJ_CLIENT) $(FT_PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(FT_PRINTF) $(LIBFT) -o $@

%.o: %.c include/minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

$(FT_PRINTF):
	@cd $(FT_PRINTF_DIR) && make

$(LIBFT):
	@cd $(LIBFT_DIR) && make

clean:
	@cd $(FT_PRINTF_DIR) && make clean
	@cd $(LIBFT_DIR) && make clean
	@rm -f $(OBJ_SERVER) $(OBJ_CLIENT) $(SERVER) $(CLIENT)

fclean: clean
	@cd $(FT_PRINTF_DIR) && make fclean
	@cd $(LIBFT_DIR) && make fclean

re: fclean all

.PHONY: all clean fclean re
