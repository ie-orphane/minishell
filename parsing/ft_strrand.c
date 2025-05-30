/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:17:07 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/22 11:17:17 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	__join(char **str, char c)
{
	char	*tmp;

	tmp = *str;
	*str = ft_strjoinc(*str, c);
	free(tmp);
}

char	*ft_strrand(size_t len)
{
	int		fd;
	ssize_t	bytes_read;
	char	buffer;
	char	*str;

	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (perror("open"), NULL);
	str = ft_strdup("");
	while (true)
	{
		bytes_read = read(fd, &buffer, 1);
		if (bytes_read == -1)
			return (perror("read"), close(fd), NULL);
		if (bytes_read == 0)
			break ;
		if (ft_isalnum(buffer) || buffer == '_')
		{
			__join(&str, buffer);
			if (ft_strlen(str) == len)
				break ;
		}
	}
	return (close(fd), str);
}
