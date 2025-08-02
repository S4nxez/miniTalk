SERVER = server
CLIENT = client
FT_PRINTF_DIR = include/ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

SRC_SERVER = src/server.c src/utils.c
SRC_CLIENT = src/client.c src/utils.c
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)


CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include -I $(FT_PRINTF_DIR)/include -fsanitize=address -fno-omit-frame-pointer -g

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_SERVER) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(FT_PRINTF) -o $@

$(CLIENT): $(OBJ_CLIENT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(FT_PRINTF) -o $@

%.o: %.c include/minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

$(FT_PRINTF):
	@cd $(FT_PRINTF_DIR) && make

clean:
	@cd $(FT_PRINTF_DIR) && make clean
	@rm -f $(OBJ_SERVER) $(OBJ_CLIENT) $(SERVER) $(CLIENT)

fclean: clean
	@cd $(FT_PRINTF_DIR) && make fclean

re: fclean all

.PHONY: all clean fclean re
