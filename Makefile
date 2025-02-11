# Variables
NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

BLD_DIR = build
SRC_DIR = src

SRCS = $(SRC_DIR)/main.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BLD_DIR)/%.o)

INCS = -Iinc/ -Ilib/libft/
LIBS = -Llib/libft/ -lft

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BLD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

clean:
	rm -rf $(BLD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re