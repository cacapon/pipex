# Variables
NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

BLD_DIR = build
SRC_DIR = src
FT_DIR  = lib/libft

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/get_command_path.c $(SRC_DIR)/cmd_split.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BLD_DIR)/%.o)

INCS = -Iinc/ -Ilib/libft/
LIBS = -L$(FT_DIR) -lft

# Rules
all: $(NAME)

## main
$(NAME): $(FT_DIR)/libft.a $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BLD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

## libft
$(FT_DIR)/libft.a: $(FT_DIR)/libft.h
	$(MAKE) -C $(FT_DIR) bonus

$(FT_DIR)/libft.h:
	git submodule update -i --recursive

## cmds
clean:
	rm -rf $(BLD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re