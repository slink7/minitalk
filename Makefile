
CLIENT_SRC =\
	main_client.c\
	send.c

SERVER_SRC =\
	main_server.c\
	t_rstack.c

OBJ_DIR = obj
CLIENT_OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(CLIENT_SRC)))))
SERVER_OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(SERVER_SRC)))))

CLIENT_NAME = client
SERVER_NAME = server

CFLAGS = -Werror

all : $(OBJ_DIR) $(CLIENT_NAME) $(SERVER_NAME)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm $(CLIENT_NAME)
	rm $(SERVER_NAME)

$(CLIENT_NAME) : $(CLIENT_OBJ)
	cc -o $(CLIENT_NAME) $(CLIENT_OBJ) -Llibft -lft

$(SERVER_NAME) : $(SERVER_OBJ) 
	cc -o $(SERVER_NAME) $(SERVER_OBJ) -Llibft -lft

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c
	cc -g3 $(CFLAGS) -o $@ -c $< -Ilibft/