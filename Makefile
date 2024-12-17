
NAME	= minishell

CFLAGS	:= -Wall -Wextra -Werror -g -fsanitize=address
# CFLAGS	+= -O3 -march=native
# CFLAGS	+= -fsanitize=address -pthread

CC		= cc
ARCHIVE = ar -rcs

LIBFT_DIR	= ./libft

LIBFT	= $(LIBFT_DIR)/build/libft.a

LINKERS	= -lm -lreadline

INCLUDE_DIRS = -I incl -I $(LIBFT_DIR)/include

HEADERS = incl/minishell.h incl/parsing.h incl/execution.h incl/bottleneck.h

FILES := \
	bottleneck/did_step.c \
	bottleneck/env.c \
	bottleneck/get_argc.c \
	bottleneck/prune_entry.c \
	bottleneck/t_command.c \
	bottleneck/t_redirection.c \
	\
	execution/children.c \
	execution/close.c \
	execution/free.c \
	execution/free_utils.c \
	execution/init_paths.c \
	execution/main.c \
	execution/pipex.c \
	execution/redirect.c \
	execution/redirect_utils.c \
	execution/segf_utils.c \
	\
	execution/builtins/builtin.c \
	execution/builtins/builtin_utils.c \
	execution/builtins/cd.c \
	execution/builtins/export.c \
	execution/builtins/pwd.c \
	execution/builtins/exit.c \
	execution/builtins/unset.c \
	execution/builtins/echo.c \
	\
	integration/main.c \
	integration/parse.c \
	integration/process.c \
	integration/sighandlers.c \
	integration/sigswitch.c \
	\
	parsing/check_consistency.c \
	parsing/condense_command.c \
	parsing/cwd.c \
	parsing/expand_variables.c \
	parsing/expand_wildcards.c \
	parsing/extract_word.c \
	parsing/is_char_type.c \
	parsing/is_token_effect.c \
	parsing/is_token_type.c \
	parsing/lex.c \
	parsing/lex_sentence.c \
	parsing/mark_tokens.c \
	parsing/match_entry.c \
	parsing/quotation.c \
	parsing/read_command.c \
	parsing/read_redirections.c \
	parsing/reduce_sentence.c \
	parsing/sentence.c \
	parsing/split_tokens.c \
	parsing/print_sentence.c \
	\
	parsing/token_consistency/close_brace.c \
	parsing/token_consistency/logic_symbol.c \
	parsing/token_consistency/open_brace.c \
	parsing/token_consistency/pipe.c \
	parsing/token_consistency/redirection.c \
	parsing/token_consistency/word.c \
	\
	parsing/token_identification/ampersand.c \
	parsing/token_identification/dollarsign.c \
	parsing/token_identification/left_arrow.c \
	parsing/token_identification/left_brace.c \
	parsing/token_identification/pipe_line.c \
	parsing/token_identification/right_arrow.c \
	parsing/token_identification/right_brace.c \
	parsing/token_identification/star.c

PARSE_FILES := \
	integration/parsetest.c

OBJECTS := $(FILES:.c=.o)

PARSE_OBJECTS := $(PARSE_FILES:.c=.o)

FILES := $(patsubst %.c, src/%.c, $(FILES))
OBJECTS := $(patsubst %.o, build/%.o, $(OBJECTS))

PARSE_FILES := $(patsubst %.c, src/%.c, $(PARSE_FILES))
PARSE_OBJECTS := $(patsubst %.o, build/%.o, $(PARSE_OBJECTS))

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) all

$(NAME): build $(LIBFT) $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LINKERS) $(LIBFT) -o $(NAME)

parsetest.out: build $(LIBFT) $(OBJECTS) $(PARSE_OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJECTS) $(PARSE_OBJECTS) $(LINKERS) $(LIBFT) -o parsetest.out

build:
	mkdir build
	mkdir build/bottleneck
	mkdir build/bottleneck/debug
	mkdir build/execution
	mkdir build/execution/builtins
	mkdir build/integration
	mkdir build/parsing
	mkdir build/parsing/token_consistency
	mkdir build/parsing/token_identification

build/%.o: src/%.c $(HEADERS)
	$(CC) -c $(INCLUDE_DIRS) $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS)
	rm -rf $(PARSE_OBJECTS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf parsetest.out
	rm -rf build
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re