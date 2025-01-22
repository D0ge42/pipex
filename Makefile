NAME = pipex
LIBFT = libft/libft.a

SRC = pipex.c commands_handler.c error_handler.c error_handler2.c utils.c get_next_line_pipex.c

OBJS = $(SRC:.c=.o) # Esclude i file oggetto di libft

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -gdwarf-4
RM = rm -rf
AR = ar crs

# Regola per creare l'eseguibile
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) -o pipex $(CFLAGS) $(OBJS) -Llibft -lft
	@echo "\033[32m$(NAME) compiled :D\033[0m"

# Regola per creare i file .o
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Regola all
all: $(NAME) libft

bonus: all

$(LIBFT): 
	@$(MAKE) --no-print-directory -C libft

# Pulizia degli oggetti
clean:
	@$(RM) $(OBJS)
	@$(MAKE) --no-print-directory -C libft clean

# Pulizia completa
fclean: clean
	@$(RM) $(NAME) $(LIBFT)

# Ricostruzione completa
re: fclean all

.PHONY: all clean fclean re bonus