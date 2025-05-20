/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:25:33 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/15 10:38:16 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	*ft_free(char **buffer, char *tmp)
{
	free(*buffer);
	*buffer = tmp;
	return (NULL);
}

static char	*get_new_line(char **stash)
{
	char	*line;
	size_t	newline_index;
	char	*tmp;

	line = NULL;
	tmp = NULL;
	if (*stash && **stash)
	{
		if (ft_strchr(*stash, '\n'))
		{
			newline_index = ft_strchr(*stash, '\n') - *stash;
			line = ft_substr(*stash, 0, newline_index + 1);
			if (line)
				tmp = ft_strdup(*stash + newline_index + 1);
		}
		else
			line = ft_strdup(*stash);
	}
	ft_free(stash, tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*tmp;
	char		*buffer;
	ssize_t		bytes_read;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (ft_free(&stash[fd], NULL));
	buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(&stash[fd], NULL));
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read < 0)
			return (ft_free(&buffer, NULL), ft_free(&stash[fd], NULL));
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(stash[fd], buffer);
		ft_free(&stash[fd], tmp);
		if (ft_strchr(stash[fd], '\n'))
			break ;
	}
	ft_free(&buffer, NULL);
	return (get_new_line(&stash[fd]));
}
