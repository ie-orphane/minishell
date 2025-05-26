#include "parsing.h"

void	ft_putstrs_fd(char **s, int fd)
{
	if (s == NULL || fd < 0)
		return ;
	while (*s)
	{
		ft_putstr_fd(*s, fd);
        s++;
	}
}
