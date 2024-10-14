#Variable general
NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -Iinclude/

# Détection du système d'exploitation
UNAME_S := $(shell uname -s)

# Configuration de l'echo selon le système
ifeq ($(UNAME_S),Linux)
    ECHO := echo -e
else
    ECHO := echo
endif

# Colors
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
CYAN=\033[0;36m
NC=\033[0m

#philo utils
PHILO_UTILS = $(addprefix utils/, ft_isdigit.c ft_atoi.c time.c print.c ft_free.c)

#philo main
PHILO = main.c error.c init.c actions.c philo.c

#philo sources
PHILO_SRCS = $(addprefix src/, $(PHILO) $(PHILO_UTILS))
PHILO_OBJS = $(PHILO_SRCS:src/%.c=obj/%.o)

# Compilation rules
all: $(NAME)

$(NAME): $(PHILO_OBJS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) $(PHILO_OBJS) -o philo
	@$(ECHO) "${YELLOW}Executable $(NAME) created.${NC}"

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(ECHO) "\r${CYAN}Compiling $<...${NC}"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
clean:
	@rm -rf obj
	@$(ECHO) "${GREEN}Object files cleaned.${NC}"

fclean: clean
	@rm -f $(NAME)
	@$(ECHO) "${RED}All files removed.${NC}"

re: fclean all

.PHONY: all clean fclean re
