NAME		=	minishell
CC			=	gcc
CFLAGS		=	-fsanitize=address -Wall -Wextra -Werror -g
RM			=	rm -rf
SRC_DIR 	= 	srcs
SRC		 	=	$(notdir $(shell find $(SRC_DIR) -type f -name *.c))
LIBFT_DIR	=	libft
OBJ_DIR		=	obj
OBJ 		= 	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
COMP_LINUX	=	-L $(LIBFT_DIR) -lft -ltermcap
INC_DIR		=	includes
INC			=	$(shell find $(INC_DIR) -type f -name "*.h")
IFLAGS 		=	-I $(LIBFT_DIR)/includes -I $(INC_DIR)
vpath			%.c $(shell find $(SRC_DIR) -type d)
.SUFFIXES: 		.c .o .h

_YELLOW		=	\033[38;5;184m
_GREEN		=	\033[38;5;46m
_RESET		=	\033[0m
_INFO		=	[$(_YELLOW)INFO$(_RESET)]
_SUCCESS	=	[$(_GREEN)SUCCESS$(_RESET)]
_CLEAR		=	\033[2K\c

all				:	init $(NAME)
					@ echo "$(_SUCCESS) Compilation done"

bonus			:	all

init			:	
					@ $(shell mkdir -p $(OBJ_DIR))
					@ $(MAKE) --silent -C $(LIBFT_DIR)
					
$(NAME)			:	$(OBJ) $(INC)
					@ echo "$(_INFO) Initialize $(NAME)"
				 	@ $(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJ) $(COMP_LINUX) 

$(OBJ_DIR)/%.o	:	%.c
					@ echo "\t$(_YELLOW)Compiling$(_RESET) $*.c\r\c"
					@ $(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
					@ echo "$(_CLEAR)"

clean			:
					@ echo "$(_INFO) Deleted object files and directories"
					@ $(RM) $(OBJ_DIR)
					@ $(MAKE) clean --silent -C $(LIBFT_DIR)
					@ echo "$(_SUCCESS) Working directory clean"

fclean			:	clean
					@ $(MAKE) fclean --silent -C $(LIBFT_DIR)
					@ $(RM) $(NAME)

re				: 	fclean all

norminette		:
					@ ~/.norminette/norminette.rb $(SRC_DIR)
					@ ~/.norminette/norminette.rb $(INC_DIR)

.PHONY: 		all fclean clean re
