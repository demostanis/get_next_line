#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <sys/syscall.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_read_ret
{
	ssize_t	n;
	char	c;
}			t_read_ret;

char	*get_next_line(int fd);

#endif
