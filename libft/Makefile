NAME		=	libft.a
CC			=	gcc
CFLAGS		=	-fsanitize=address -Wall -Wextra -Werror
AR 			= 	ar
ARFLAGS 	=	rcs
RM			=	rm -rf
SRC_DIR		=	srcs
INC_DIR		= 	includes
IFLAGS 		=	-I $(INC_DIR)
SRC 		=	$(notdir $(shell find $(SRC_DIR) -type f -name *.c))
OBJ_DIR		=	obj
OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
vpath 			%.c $(shell find $(SRC_DIR) -type d)
.SUFFIXES: 		.c .o .h

_YELLOW		=	\033[38;5;184m
_GREEN		=	\033[38;5;46m
_RESET		=	\033[0m
_INFO		=	[$(_YELLOW)INFO$(_RESET)]
_SUCCESS	=	[$(_GREEN)SUCCESS$(_RESET)]
_CLEAR		=	\033[2K\c

all				:	init $(NAME)
					@ echo "$(_SUCCESS) libft.a created"

init			:
					@ echo "$(_INFO) Initializing libft..."
					@ $(shell mkdir -p $(OBJ_DIR))

$(NAME)			:	$(OBJ)
					@ echo "\t$(_YELLOW)Creating Library...$(_RESET)\r\c"
					@ $(AR) $(ARFLAGS) $(NAME) $(OBJ)
					@ echo "$(_CLEAR)"

$(OBJ_DIR)/%.o	:	%.c
					@ echo "\t$(_YELLOW)Compiling$(_RESET) $*.c\r\c"
					@ $(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
					@ echo "$(_CLEAR)"

clean			:
					$(RM) $(OBJ_DIR)
				
fclean			:	clean
					$(RM) $(NAME)

re				: 	fclean all

.PHONY: 		all fclean clean re
