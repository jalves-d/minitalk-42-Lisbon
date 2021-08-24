
CC = gcc

CFLAGS = -Werror -Wall -Wextra -fsanitize=address -g

SERVER = server
SERVER_SRCS = ft_server.o

CLIENT = client
CLIENT_SRCS = ft_client.o

all : $(SERVER) $(CLIENT)

$(CLIENT) : $(CLIENT_SRCS)
	@$(CC) $(CLIENT_SRCS) -o $(CLIENT) $(CFLAGS)

$(SERVER) : $(SERVER_SRCS)
	@$(CC) $(SERVER_SRCS) -o $(SERVER) $(CFLAGS)

%.o : %.c
	@$(CC) $(CFLAGS) $< -c

clean :
	@rm -f ft_client.o ft_server.o

fclean : clean
	@rm -f $(SERVER) $(CLIENT)

re : fclean all

.PHONY: all clean fclean re
