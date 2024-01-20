
CLIENT_SRC =\
	main_client.c\
	chrono.c\
	send.c

SERVER_SRC =\
	main_server.c\
	chrono.c\
	t_rstack.c

OBJ_DIR = obj
CLIENT_OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(CLIENT_SRC)))))
SERVER_OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(SERVER_SRC)))))

NAME =
CLIENT = client
SERVER = server

CFLAGS = -Werror

bonus : all

all : $(OBJ_DIR) $(CLIENT) $(SERVER)

clean :
	rm -rf $(OBJ_DIR) || true

fclean : clean
	rm $(SERVER) || true
	rm $(CLIENT) || true

re : fclean all

$(CLIENT) : $(CLIENT_OBJ)
	cc -o $(CLIENT) $(CLIENT_OBJ) -Llibft -lft

$(SERVER) : $(SERVER_OBJ) 
	cc -o $(SERVER) $(SERVER_OBJ) -Llibft -lft

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c
	cc -g3 $(CFLAGS) -o $@ -c $< -Ilibft/