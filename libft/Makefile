NAME = libft.a # Name of the file that will be generated.

SRC = ft_atoi.c    \
       ft_bzero.c   \
       ft_calloc.c  \
       ft_isalnum.c \
       ft_isalpha.c \
       ft_isascii.c \
       ft_isdigit.c \
       ft_isprint.c \
       ft_memchr.c  \
       ft_memcmp.c  \
       ft_memcpy.c  \
       ft_memmove.c \
       ft_memset.c  \
       ft_putchar_fd.c \
       ft_putendl_fd.c \
       ft_putnbr_fd.c \
       ft_putstr_fd.c \
       ft_split.c  \
       ft_strchr.c \
       ft_strdup.c \
       ft_striteri.c \
       ft_strjoin.c \
       ft_strlcat.c \
       ft_strlcpy.c \
       ft_strlen.c \
       ft_strmapi.c \
       ft_strncmp.c \
       ft_strnstr.c \
       ft_strrchr.c \
       ft_strtrim.c \
       ft_substr.c \
       ft_tolower.c \
       ft_toupper.c \
       ft_itoa.c \
	   ft_lstadd_back.c  \
	   ft_lstadd_front.c \
	   ft_lstclear.c     \
	   ft_lstdelone.c    \
	   ft_lstiter.c      \
	   ft_lstlast.c      \
	   ft_lstmap.c       \
	   ft_lstnew.c       \
	   ft_lstsize.c	\
	   ft_utils.c \
	   ft_utils2.c \
	   ft_utils3.c \
	   ft_utils4.c \
	   get_next_line_bonus.c \
	   get_next_line_utils_bonus.c \
	   hexa_handler.c \
	   info_gatherer.c \
	   pointer_handler.c \
	   string_handler.c \
	   struct_handler.c \
	   type_handler.c \
	   type_handler.c \
	   unsigned_handler.c\
	   ft_printf.c\
	   char_handler.c\
	   integers_handler.c\
	   ft_printnbr_count.c\
	   ft_print_hexa.c\
	   ft_print_pointer.c\
	   ft_putstr_count.c
       

OBJS = $(SRC:.c=.o) # This variable will convert src .c files to object files .o

CC = cc # Compiler that is going to be used
CFLAGS = -Wall -Werror -Wextra # Flags
RM = rm -rf # Command used to remove files or directories
AR = ar crs # Command used to create archives (static library)

# RULES

# In order to create the library libft.a all the object files must exist.
$(NAME): $(OBJS)
	@$(AR) $@ $^
	@echo "\033[32m$(NAME) compiled :D ヽ༼ ຈل͜ຈ༼ ▀̿̿Ĺ̯̿̿▀̿ ̿༽Ɵ͆ل͜Ɵ͆ ༽ﾉ \033[0m"

%.o: %.c # Generic rule that specifies that every .c file must be compiled into a .o file
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME) # Default target. It will build libft.a. This is what will be executed if we just execute 'make'

clean: # This rule will delete all the .o files and bonus .o files. It won't erase $(NAME).
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all # This will first execute fclean and then all. This will make sure everything will be compiled using new files, without using cached or old files.

.PHONY: all clean fclean re # Without using .PHONY make can be tricked by the presence of files with the same names as the targets and decide not to run the targets. 
# With .PHONY make will always execute the targets, even if files with the same name exist, ensuring that commands will always be executed.