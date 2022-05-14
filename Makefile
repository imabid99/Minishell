# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 12:34:40 by obeaj             #+#    #+#              #
#    Updated: 2022/05/14 14:04:55 by obeaj            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the final executable
NAME = minishell

# Project's directories
SOURCEDIR := ./src
HEADERSDIR := ./includes
OBJECTSDIR := ./objects
EXEC_FOLDER = executor
BN_FOLDER = builtins
PARS_FOLDER = parser
GC_FOLDER = garbage
EXPA_FOLDER = expander
READ_FOLDER = readline
LIBFT_HEADER = ./libft
LIBFT_FOLDER = libft


# Name of variables
LIBFT_LIB = libft.a
LIBS = -lncurses -L /goinfre/imabid/.brew/opt/readline/lib
RD_INCLUDE = /goinfre/imabid/.brew/opt/readline/include/
LIBFT = libft
FLAGS = -Wall -Wextra -Werror


# Execution files variable
EXEC_FILES =  exec_tree.c \
executor_utils.c \
executor_utils1.c \
executor.c \
ft_execve.c \

# garbage collector files variable

GC_FILES = garbage.c \

# Parse files variable

PARS_FILES = ast_utils_1.c \
lexer_utils.c \
lexer.c \
list_utils.c \
parsing.c \
parsing_utils.c \
parsing_utils_1.c \
syntax_analyzer_utils.c \
syntax_analyzer.c \
tokenizer_utils.c \
tokenizer_utils_1.c \
tokenizer.c \
utils.c \

# Readline files variable

READ_FILES = chars_list_rest.c \
chars_list.c \
get_input.c \
history.c \
line_nodes.c \
readline.c \
terminal_config.c

# Expansion files variable

EXPA_FILES = expander_utils.c \
expander.c \
glob_utils_1.c \
glob_utils_2.c \
glob_utils.c \

# Builtins files variable

BN_FILES = cd.c \
echo.c \
env.c \
exit.c \
export_utils.c \
export.c \
pwd.c \
unset.c \
signal_handlers.c \

# Main file variable

MAIN_FILE = minishell.c \

# Define objects for all sources
OBJ_EXEC = $(addprefix $(OBJECTSDIR)/$(EXEC_FOLDER)/, $(EXEC_FILES:.c=.o))
OBJ_BN = $(addprefix $(OBJECTSDIR)/$(BN_FOLDER)/, $(BN_FILES:.c=.o))
OBJ_EXPA = $(addprefix $(OBJECTSDIR)/$(EXPA_FOLDER)/, $(EXPA_FILES:.c=.o))
OBJ_PARS = $(addprefix $(OBJECTSDIR)/$(PARS_FOLDER)/, $(PARS_FILES:.c=.o))
OBJ_GC = $(addprefix $(OBJECTSDIR)/$(GC_FOLDER)/, $(GC_FILES:.c=.o))
OBJ_MAIN = $(addprefix $(OBJECTSDIR)/, $(MAIN_FILE:.c=.o))
OBJS := $(OBJ_EXEC) $(OBJ_BN) $(OBJ_EXPA) $(OBJ_PARS) $(OBJ_MAIN) $(OBJ_GC)
LIBFT_FILE := $(LIBFT_FOLDER)/$(LIBFT_LIB)

# Name the compiler
CC = gcc

# OS specific part
RM = rm -rf
RMDIR = rm -rf
MKDIR = mkdir -p
MAKE = make -C
ECHO = /bin/echo
ERRIGNORE = 2>/dev/null

.PHONY: all fclean


all: credit $(NAME)

$(NAME): $(OBJS)
	@echo "█████████████████████████ Making LIBFT █████████████████████████"
	make -C $(LIBFT_FOLDER)
	@$(CC) -I $(HEADERSDIR) -I $(LIBFT_FOLDER) $(OBJS) $(LIBFT_FOLDER)/$(LIBFT_LIB) $(LIBS) -o $@ -lreadline
	@echo "███████████████████████ Compiling is DONE ██████████████████████"

$(OBJECTSDIR)/%.o : $(SOURCEDIR)/%.c $(HEADERSDIR)/*.h
	@$(MKDIR) $(dir $@)
	@echo "Compiling $<: {DONE}"
	@$(CC) $(FLAGS) -I $(HEADERSDIR) -I $(LIBFT_HEADER) -I $(RD_INCLUDE) -o $@ -c $<

# Remove all objects, dependencies and executable files generated during the build

clean:
	@echo "deleting: " $(OBJECTSDIR)
	@$(RMDIR) $(OBJECTSDIR) $(ERRIGNORE)
	@echo "deleting: " "libft objects"
	@$(MAKE) $(LIBFT_FOLDER) clean

fclean: clean
	@echo "$(RED)deleting$(RESET): " $(LIBFT_FOLDER)/$(LIBFT_LIB)
	@$(RM) $(LIBFT_FOLDER)/$(LIBFT_LIB) $(ERRIGNORE)
	@echo "$(RED)deleting$(RESET): " $(NAME)
	@$(RM) $(NAME) $(ERRIGNORE)

re: fclean credit $(NAME)

credit:
	@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "         Made with love by : obeaj and imabid"
	@echo "███████████████████████ Making minishell ███████████████████████"
