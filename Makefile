NAME                = minishell
CC                  = cc
FLAGS               = -Wall -Wextra -Werror #-fsanitize=address
READ                = -lreadline

INC                 = -I INCLUDES -Ilibft/includes -Ilibft/libft -Ilibft/ft_malloc
LIB_A               = libftprintf.a

ASSIST_SRC_LIST		= helper.c init.c
BUILTINS_SRC_LIST	= cd.c echo.c env.c exit.c export.c export_support.c pwd.c unset.c
LEXER_SRC_LIST      = lexer.c backstage.c episode_one.c episode_two.c episode_three.c last_episode.c
EXPANDER_SRC_LIST   = expander.c build_cmd.c creators.c deletion.c environment_utils.c expansion.c \
					list_operations.c pattern_matching.c redirections.c
EXECUTER_SRC_LIST   = executer.c exec_utils.c dup_utils.c close_utils.c checkers.c builtins.c _execve.c
MINISHELL_SRCS_LIST = minishell.c ms_errors.c

ASSIST_SRCS_PATH	= $(addprefix srcs/assist/,$(ASSIST_SRC_LIST))
BUILTINS_SRC_PATH	= $(addprefix srcs/builtins/,$(BUILTINS_SRC_LIST))
LEXER_SRCS_PATH     = $(addprefix srcs/lexer/,$(LEXER_SRC_LIST))
EXPANDER_SRCS_PATH  = $(addprefix srcs/expander/,$(EXPANDER_SRC_LIST))
EXECUTER_SRC_PATH   = $(addprefix srcs/executer/,$(EXECUTER_SRC_LIST))
MINISHELL_SRCS_PATH = $(addprefix srcs/minishell/,$(MINISHELL_SRCS_LIST))

SOURCES_LIST        = $(LEXER_SRC_LIST) $(EXPANDER_SRC_LIST) $(EXECUTER_SRC_LIST) \
					  $(MINISHELL_SRCS_LIST) $(BUILTINS_SRC_LIST) $(ASSIST_SRC_LIST)

SOURCES             = $(LEXER_SRCS_PATH) $(EXPANDER_SRCS_PATH) $(EXECUTER_SRC_PATH) \
					  $(MINISHELL_SRCS_PATH) $(BUILTINS_SRC_PATH) $(ASSIST_SRC_PATH)


OBJECTS_DIRECTORY   = OBJECTS/
OBJECTS_LIST        = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS             = $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS

GREEN               = \033[0;32m
RED                 = \033[0;31m
RESET               = \033[0m

all: libcomp $(NAME)

libcomp :
	@make -C LIBFT/
	@cp LIBFT/$(LIB_A) .

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
	@tput el
	@$(CC) $(FLAGS) $(READ) $(OBJECTS) $(LIB_A) -o $(NAME)
	@echo "$(RESET)\n$(NAME): $(GREEN)$(NAME) object files was created"
	@echo "$(RESET)$(NAME): $(GREEN)$(NAME) was created"

$(OBJECTS_DIRECTORY):
	mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : srcs/lexer/%.c
	@tput cuu1
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "Compiling $(GREEN)$@"

$(OBJECTS_DIRECTORY)%.o : srcs/expander/%.c
	@tput cuu1
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "Compiling $(GREEN)$@"

$(OBJECTS_DIRECTORY)%.o : srcs/executer/%.c
	@tput cuu1
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "Compiling $(GREEN)$@"

$(OBJECTS_DIRECTORY)%.o : srcs/minishell/%.c
	@tput cuu1
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "Compiling $(GREEN)$@"

$(OBJECTS_DIRECTORY)%.o : srcs/builtins/%.c
	@tput cuu1
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "Compiling $(GREEN)$@"

$(OBJECTS_DIRECTORY)%.o : srcs/assist/%.c
	@tput cuu1
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "Compiling $(GREEN)$@"

.PHONY: all clean fclean re

clean:
	@rm -rf $(OBJECTS_DIRECTORY)
	@make clean -C LIBFT/

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIB_A)
	@make fclean -C LIBFT/

re:
	@$(MAKE) fclean
	@$(MAKE) all