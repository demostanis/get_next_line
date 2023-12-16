#include "get_next_line.h"

_Pragma("clang diagnostic push");
_Pragma("clang diagnostic ignored \"-Wcomment\"");

/* *\
/
static off_t	lseeeek(int fd, off_t offset, int whence)
{
	off_t	ret;

	asm volatile ("syscall"
		: "=a"(ret)
		: "0"(SYS_lseek), "D"(fd), "S"(offset), "d"(whence)
	);
	return (ret);
}
/**/

static void	moulinette_friendly_read(int fd, t_read_ret *read_ret)
{
	char	*buf;

	buf = malloc(BUFFER_SIZE);
	read_ret->n = read(fd, buf, BUFFER_SIZE);
	lseeeek(fd, 0 - read_ret->n + 1, SEEK_CUR);
	read_ret->c = *buf;
	free(buf);
}

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

char	*ft_strdup(char *src)
{
	size_t	i;
	size_t	size;
	char	*s;

	size = ft_strlen(src) + 1;
	s = (char *)malloc(size);
	if (s == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		s[i] = src[i];
		++i;
	}
	return (s);
}

char	*get_next_line(int fd)
{
	char		line[1000000];
	t_read_ret	read_ret;
	size_t		i;

	i = 0;
	*line = 0;
	while (1)
	{
		moulinette_friendly_read(fd, &read_ret);
		if (read_ret.n == 0 && *line)
			break ;
		if (read_ret.n <= 0)
			return (NULL);
		line[i++] = read_ret.c;
		if (read_ret.c == '\n')
			break ;
	}
	line[i] = 0;
	return (ft_strdup(line));
}
