# Variables
NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

# directory
BLD_DIR = build
FT_DIR  = lib/libft
MAN_S_DIR = src/mandatory
CMN_S_DIR = src/common
BNS_S_DIR = src/bonus

# src
MAN_SRC = main.c
BNS_SRC = main.c
CMN_SRC = get_cmd_path.c cmd_split.c open_file.c error.c exec_free.c
CMN_SRCS = $(addprefix $(CMN_S_DIR)/,$(CMN_SRC))

ifeq ($(MAKECMDGOALS), bonus)
	BNS_SRCS = $(addprefix $(BNS_S_DIR)/,$(BNS_SRC))
	OBJS = $(BNS_SRCS:$(BNS_S_DIR)/%.c=$(BLD_DIR)/%.o) \
		   $(CMN_SRCS:$(CMN_S_DIR)/%.c=$(BLD_DIR)/%.o)
else
	MAN_SRCS = $(addprefix $(MAN_S_DIR)/,$(MAN_SRC))
	OBJS = $(MAN_SRCS:$(MAN_S_DIR)/%.c=$(BLD_DIR)/%.o) \
		   $(CMN_SRCS:$(CMN_S_DIR)/%.c=$(BLD_DIR)/%.o)
endif

INCS = -Iinc/ -Ilib/libft/
LIBS = -L$(FT_DIR) -lft

# Rules
all: $(NAME)
bonus: $(NAME)

## main
$(NAME): $(FT_DIR)/libft.a $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

ifeq ($(MAKECMDGOALS), bonus)
$(BLD_DIR)/%.o: $(BNS_S_DIR)/%.c
	@mkdir -p $(BLD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)
else
$(BLD_DIR)/%.o: $(MAN_S_DIR)/%.c
	@mkdir -p $(BLD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)
endif

$(BLD_DIR)/%.o: $(CMN_S_DIR)/%.c
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
	$(MAKE) -C $(FT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(FT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re