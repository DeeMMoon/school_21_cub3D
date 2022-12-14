#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include "../libft/headers/libft.h"

char	*get_next_line(int fd);
char	*ft_strchr_gnl(const char *string, int symbol);
char	*ft_strdup_gnl(const char *s1);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);

size_t	ft_strlen_gnl(const char *str);

#endif