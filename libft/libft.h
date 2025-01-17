/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:32:35 by lorenzo           #+#    #+#             */
/*   Updated: 2024/08/13 18:32:37 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>

/*-------------------------------------------------------/
/                      PRINTF                            /
/-------------------------------------------------------*/
/*Main structure. Handles everything as if each variable is a light switch.
Depending on if it's turned on or off a different output will be produced*/

typedef struct s_format
{
	int				minus;
	int				hashtag;
	int				plus;
	int				space;
	int				zero;
	int				width;
	int				precision;
	char			conversion;
}					t_format;

/*Utils*/

size_t				ft_strlen(char *str);
int					is_conversion(char c);
int					is_flag(char c);
int					is_digit(char c);
int					perc_counter(char c, const char *str);
int					count_digits(long long num);
int					count_hex_digits(unsigned int num);
int					count_memory_address_length(unsigned long long ptr);
int					max(int a, int b);
int					count_udigits(unsigned int num);
int					ft_atoi(const char *str);
int					ft_strchr(int c, const char *str);
void				jump_index(const char *format, int *i);
void				space_writer(int spaces, int *count);
void				zero_writer(int zeros, int *count);
void				free_structs(t_format **struct_array, const char *format);
void				initialize_struct(t_format *new_s);

/*Main function*/

int					ft_printf(const char *format, ...);

/*Different types paddings*/

void				id_left_padding(t_format *new_s, long long nb, int *count,
						int spaces);
void				id_right_padding(t_format *new_s, long long nb, int *count,
						int spaces);
void				id_no_padding(t_format *new_s, long long nb, int *count);
void				u_left_padding(t_format *new_s, unsigned int nb, int *count,
						int spaces);
void				u_right_padding(t_format *new_s, unsigned int nb,
						int *count, int spaces);
void				u_no_padding(t_format *new_s, unsigned int nb, int *count);
void				hexa_left_padding(t_format *new_s, unsigned int nb,
						int *count, int spaces);
void				hexa_right_padding(t_format *new_s, unsigned int nb,
						int *count, int spaces);
void				hexa_no_padding(t_format *new_s, unsigned int nb,
						int *count);
void				p_left_padding(t_format *new_s, unsigned long long nb,
						int *count, int spaces);
void				p_right_padding(t_format *new_s, unsigned long long nb,
						int *count, int spaces);
void				p_no_padding(t_format *new_s, unsigned long long nb,
						int *count);

/*Handlers*/
void				string_handler(t_format *new_s, va_list args, int *count);
void				char_handler(t_format *new_s, va_list args, int *count);
void				int_handler(t_format *new_s, va_list args, int *count);
void				uint_handler(t_format *new_s, va_list args, int *count);
void				hexa_handler(t_format *new_s, va_list args, int *count);
void				p_handler(t_format *new_s, va_list args, int *count);

/*Printers*/
void				ft_print_pointer(uintptr_t nb, int *count);
void				ft_print_hexa(unsigned int nb, int *count, char c);
void				ft_printnb_count(long long int nb, int *count,
						t_format *new_s);
void				ft_printunb_count(unsigned int nb, int *count);
void				ft_putstr_count(void *str2, int *count, t_format *new_s,
						int len);
void				ft_putchar_count(char c, int *count);
void				space_writer(int spaces, int *count);
void				zero_writer(int zeros, int *count);
void				ft_putstr(char *str);

/*Struct handleer*/

void				struct_to_string(t_format *new_s, va_list args, int *count);
t_format			*create_struct(const char *format);
t_format			**create_struct_array(const char *format);
void				get_flags(t_format *new_s, const char *format);
int					get_width(const char *format);
int					get_precision(const char *format);
void				get_conversion(const char *format, t_format *new_s);

/*-------------------------------------------------------/
/                      GNL                               /
/-------------------------------------------------------*/

char				*get_next_line(int fd);
char				*safe_malloc(void);
char				*ft_strdup_gnl(const char *str);
char				*ft_strjoin_gnl(char const *s1, char const *s2);

/*-------------------------------------------------------/
/                      LIBFT                             /
/-------------------------------------------------------*/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int i);
int					ft_isalpha(int i);
int					ft_isascii(int i);
int					ft_isdigit(int i);
int					ft_isprint(int i);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *s1, const void *s2, size_t n);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strdup(const char *s);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strrchr(const char *s, int c);
int					ft_tolower(int i);
int					ft_toupper(int i);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *str, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *str, int fd);
void				ft_putendl_fd(char *str, int fd);
void				ft_putnbr_fd(int nb, int fd);
t_list				*ft_lstnew(void *data);
void				ft_lstadd_back(t_list **lst, t_list *new_s);
void				ft_lstadd_front(t_list **lst, t_list *new_s);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new_s);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif
