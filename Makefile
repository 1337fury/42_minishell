NAME                = minishell
CC                  = cc
FLAGS               = -Wall -Wextra -Werror #-fsanitize=address
READ                = -lreadline

INC                 = -I INCLUDES -Ilibft/includes -Ilibft/libft
LIB_A               = libftprintf.a

LEXER_SRC_LIST      = lexer.c backstage.c episode_one.c episode_two.c episode_three.c last_episode.c
EXPANDER_SRC_LIST   = expander.c build_cmd.c creators.c deletion.c environment_utils.c expansion.c \
					list_operations.c pattern_matching.c redirections.c
EXECUTER_SRC_LIST   = executer.c exec_utils.c dup_utils.c close_utils.c checkers.c builtins.c _execve.c
MINISHELL_SRCS_LIST = minishell.c ms_errors.c

LEXER_SRCS_PATH     = $(addprefix srcs/lexer/,$(LEXER_SRC_LIST))
EXPANDER_SRCS_PATH  = $(addprefix srcs/expander/,$(EXPANDER_SRC_LIST))
EXECUTER_SRC_PATH   = $(addprefix srcs/executer/,$(EXECUTER_SRC_LIST))
MINISHELL_SRCS_PATH = $(addprefix srcs/minishell/,$(MINISHELL_SRCS_LIST))

SOURCES_LIST        = $(LEXER_SRC_LIST) $(EXPANDER_SRC_LIST) $(EXECUTER_SRC_LIST) $(MINISHELL_SRCS_LIST)
SOURCES             = $(LEXER_SRCS_PATH) $(EXPANDER_SRCS_PATH) $(EXECUTER_SRC_PATH) $(MINISHELL_SRCS_PATH)

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
	$(CC) $(FLAGS) $(READ) $(OBJECTS) $(LIB_A) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)$(NAME) object files was created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : srcs/lexer/%.c
	$(CC) $(FLAGS) $(INC) -c $< -o $@

$(OBJECTS_DIRECTORY)%.o : srcs/expander/%.c
	$(CC) $(FLAGS) $(INC) -c $< -o $@

$(OBJECTS_DIRECTORY)%.o : srcs/executer/%.c
	$(CC) $(FLAGS) $(INC) -c $< -o $@

$(OBJECTS_DIRECTORY)%.o : srcs/minishell/%.c
	$(CC) $(FLAGS) $(INC) -c $< -o $@

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